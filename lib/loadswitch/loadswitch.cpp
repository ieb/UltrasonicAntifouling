#include "loadswitch.h"







/**
 * Controlls a n-channel load switch driven by a PWM signal with the inrush current and switch state controlled
 * buy the frequency of a 50% PWM signal on pin 11.
 * 
 * The gate of the n-channel mosfet is connected to a charge pump charged by the PWM signal through a capacitor
 * and diode network. The charge is stored in a RC sized to control ramp up and ramp down ballancing power dissipation agains
 * switch on time and inrush current.
 * 
 * Once on, the switch is forced into fully conductive mode to minimise power disipation.
 * 
 * High and Low input voltages are reported as failures causing the switch to shutdown.
 * Slow charge time is considerd a failure and reported.
 * Incomplete charging is considered a failure and reported.
 */


LoadSwitch::LoadSwitch(Stream * _io) {
    io = _io;
}

void LoadSwitch::begin(int startFrequency, int runFrequency ) {
    // Timer 3 is connected to pins 11 (A) and 3 (B)
  pinMode(11, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(11,HIGH);
  delay(100);
  digitalWrite(11,LOW);
  // supply voltage on ADC0, power voltage on ADC1
  // setup the prescaler and PWM.

  
  /// hhttp://ww1.microchip.com/downloads/en/DeviceDoc/en590320.pdf 
  // page 114 for PWM description.
  // page 135


  state = LS_STATE_OFF;
  io->print(F("Getting timers"));
  io->flush();

  // f = 16000/(2*64*(1+OCRn))
  // OCRn = (16000/(2*64*f))-1;
  if ( startFrequency == 0 ) {
    startFrequencyOCR =  0xff;
  } else {
    startFrequencyOCR = (16000/(2*64*startFrequency));
  }
  if ( runFrequency == 0 ) {
    onFrequencyOCR =  0xff;
  } else {
    onFrequencyOCR = (16000/(2*64*runFrequency));
  }


  io->print(F("startFrequency f="));
  io->print(startFrequency);
  io->print(F(" ORC2A="));
  io->println(startFrequencyOCR);

  io->print(F("runFrequency f="));
  io->print(runFrequency);
  io->print(F(" ORC2A="));
  io->println(onFrequencyOCR);
  io->print(F("Done Getting timers"));

}

int LoadSwitch::getADCReading(double voltage) {
    int r = voltage/0.02738839286;
    if (r < 0) r = 0;
    if ( r > 1024 ) r = 1024;
    return r;
}

void LoadSwitch::setMaxOnTime(uint16_t ontimeInMillis) {
    ontimeMillis = ontimeInMillis;

}

void LoadSwitch::setSupplyVoltages(double min, double max) {
  minSupplyVoltageADCV = getADCReading(min);
  maxSupplyVoltageADCV = getADCReading(max);
  io->print(F("minSupplyVoltageADCV v="));
  io->print(min);
  io->print(F(" adc="));
  io->println(minSupplyVoltageADCV);
  io->print(F("maxSupplyVoltageADCV v="));
  io->print(max);
  io->print(F(" adc="));
  io->println(maxSupplyVoltageADCV);
}

void LoadSwitch::setOutputVoltage(double min, double maxDifference) {
  minOutVoltageADCV = getADCReading(min);
  maxLoadSwitchDifferenceADCV = getADCReading(maxDifference);
  io->print(F("minOutVoltageADCV v="));
  io->print(min);
  io->print(F(" adc="));
  io->println(minOutVoltageADCV);
  io->print(F("maxLoadSwitchDifferenceADCV v="));
  io->print(maxDifference);
  io->print(F(" adc="));
  io->println(maxLoadSwitchDifferenceADCV);
}




int LoadSwitch::turnOn(bool force) {
    if ( state == LS_STATE_ON ) {
        return LOADSWITCH_ON;
    }
      // set the start frequency 
    // wait till ADC1 meets requirements
    // set the run frequency
    // if ADC1 doesnt meet required frequency withing desired time, then fail
    int vin = analogRead(A0); 
    if ( !force ) {
        if (  vin < minSupplyVoltageADCV ) {
            // dont start, voltage too low
            io->println(F("Supply too low "));
            turnOff();
            return LOADSWITCH_LOW_VOLTAGE;
        } else if (  vin > maxSupplyVoltageADCV ) {
            io->println(F("Supply Too High "));
            turnOff();
            return LOADSWITCH_HIGH_VOLTAGE;
        }        
    }


    // The datasheet does seem to match these settings/
    // tken from https://www.arduino.cc/en/pmwiki.php?n=Tutorial/SecretsOfArduinoPWM
    // prescaler 64 CS11 CS10 == 1
    // CTC toggle   COM1A0 == 1
    // Mode 9, WGM20 WGM22 == 1, phase correct pwm with OCR2A setting the freequency.

    TCCR2A = _BV(COM2A0) | _BV(WGM20) ;
    TCCR2B = _BV(CS11) | _BV(CS10)  |  _BV(WGM22);
 
    OCR2A = startFrequencyOCR;
    io->println(OCR2A);
    state = LS_STATE_RAMPUP;
    unsigned long beginIngressMs = millis();
    finalStartMs = 0;
    switchOnMs = 0;
    switchFailMs = 0;
    io->println(F("Turning on"));
    unsigned long timeout = ontimeMillis;
    if (force) {
        timeout = 60000;
    }
    while((millis()-beginIngressMs) < timeout) {
        int vin = analogRead(A0);
        int vout = analogRead(A1);
        switch (state) {
            case LS_STATE_RAMPUP: // ramping upi
                if ( force) {
                    if ( millis() - beginIngressMs > 5000 ) {
                        io->println(F("Forced end of ramp up"));
                        state = LS_STATE_RAMPUP_FINAL;
                        finalStartMs = (uint16_t) (millis()-beginIngressMs);
                    }
                } else {
                    if ( vout > minOutVoltageADCV ) {
                        io->println(F("Ramped up"));
                        state = LS_STATE_RAMPUP_FINAL;
                        finalStartMs = (uint16_t) (millis()-beginIngressMs);
                    }
                }
                break;
            case LS_STATE_RAMPUP_FINAL: // ramping up, final
                if ( force) {
                    if ( millis() - beginIngressMs > 10000 ) {
                        io->println(F("Forced Fully on"));
                        state = LS_STATE_ON;
                        OCR2A = onFrequencyOCR;
                        io->println(OCR2A);
                        switchOnMs = (uint16_t) (millis()-beginIngressMs);
                        return LOADSWITCH_ON;
                    }
                } else {
                    if ( (vin - vout) < maxLoadSwitchDifferenceADCV ) {
                        io->println(F("Fully on"));
                        state = LS_STATE_ON;
                        OCR2A = onFrequencyOCR;
                        switchOnMs = (uint16_t) (millis()-beginIngressMs);
                        return LOADSWITCH_ON;
                    }
                }
                break;
        }
        delay(100);
    } 
    switchFailMs = (uint16_t) (millis()-beginIngressMs);
    // timed out, whats the problem ?
    TCCR2A = 0b00000000;
    OCR2A = 0xff;
    if ( state == LS_STATE_RAMPUP ) {
        io->println(F("Inrush fail"));
        return LOADSWITCH_INRUSH_RAMP_FAILED;
    }
    io->println(F("Stabalisation fail"));
    return LOADSWITCH_STABLISATION_FAILED;
}
void LoadSwitch::turnOff() {
    io->println(F("Turning off"));
    TCCR2A = 0x00;
    TCCR2B = 0x00;
    OCR2A = 0x00;

    state = LS_STATE_OFF;

}

int LoadSwitch::check() {

    // check the difference between supply and output.
    // if 
    int vin = analogRead(A0);
    int vout = analogRead(A1);
    if ( vin < minOutVoltageADCV ) {
       io->println(F("Turning off, output voltage too low"));
        turnOff();
        return LOADSWITCH_LOW_VOLTAGE;
    } else if ( vin > maxSupplyVoltageADCV ) {
       io->println(F("Turning off, supply voltage too high"));
        turnOff();
        return LOADSWITCH_HIGH_VOLTAGE;
    }
    if ( state == LS_STATE_OFF ) {
        return LOADSWITCH_OFF;
    }
    if ( vout < minOutVoltageADCV ) {
       io->println(F("Out voltage too low"));
        return LOADSWITCH_INRUSH_RAMP_FAILED;
    } else if ( (vin - vout) > maxLoadSwitchDifferenceADCV ) {
       io->println(F("Out voltage too far below supply"));
        return LOADSWITCH_STABLISATION_FAILED;
    } else {
       io->println(F("Loadswitch on"));
        return LOADSWITCH_ON;
    }
}





