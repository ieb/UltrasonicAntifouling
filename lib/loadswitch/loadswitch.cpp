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
  // supply voltage on ADC0, power voltage on ADC1
  // setup the prescaler and PWM.

  
  /// hhttp://ww1.microchip.com/downloads/en/DeviceDoc/en590320.pdf 
  // page 114 for PWM description.
  // page 135

  // mode needs to set TOP and PWM.
  // 0bx0xx1xxx  CTC mode WGM20 = 0, WGM21 = 1
  // 0bxx00xxxx  OC2 disconnected
  // 0bxxxxx100 64 prescalar
  // 0b00001100  result

  state = LS_STATE_OFF;
  startFrequencyOCR = getTimerOn(startFrequency);
  onFrequencyOCR = getTimerOn(runFrequency);


}

void LoadSwitch::setMaxOnTime(uint16_t ontimeInMillis) {
    ontimeMillis = ontimeInMillis;

}

void LoadSwitch::setSupplyVoltages(double min, double max) {
  minSupplyVoltageADCV = getADCReading(min);
  maxSupplyVoltageADCV = getADCReading(max);
}

void LoadSwitch::setOutputVoltage(double min, double maxDifference) {
  minOutVoltageADCV = getADCReading(min);
  maxLoadSwitchDifferenceADCV = getADCReading(maxDifference);
}


// f = 16000/(2*64*(1+OCRn))
// OCRn = (16000/(2*64*f))-1;
uint8_t LoadSwitch::getTimerOn(int frequencyKhz) {
    int n = (16000/(2*64*frequencyKhz));
    if ( n < 0 ) {
        return 0;
    } else if ( n > 255) {
        return 0xff;
    }
    return (uint8_t)n;
}


int LoadSwitch::turnOn() {
    if ( state == LS_STATE_ON ) {
        return LOADSWITCH_ON;
    }
      // set the start frequency 
    // wait till ADC1 meets requirements
    // set the run frequency
    // if ADC1 doesnt meet required frequency withing desired time, then fail
    int vin = analogRead(A0); 
    if ( vin < minSupplyVoltageADCV ) {
        // dont start, voltage too low
        turnOff();
        return LOADSWITCH_LOW_VOLTAGE;
    } else if ( vin > maxSupplyVoltageADCV ) {
        turnOff();
        return LOADSWITCH_HIGH_VOLTAGE;
    }

    TCCR2A = TCCR2A_ENABLE;
    OCR2A = startFrequencyOCR;
    state = LS_STATE_RAMPUP;
    unsigned long beginIngressMs = millis();
    finalStartMs = 0;
    switchOnMs = 0;
    switchFailMs = 0;
    while((millis()-beginIngressMs) < ontimeMillis) {
        int vin = analogRead(A0);
        int vout = analogRead(A1);
        switch (state) {
            case LS_STATE_RAMPUP: // ramping upi
                if ( vout > minOutVoltageADCV ) {
                    state = LS_STATE_RAMPUP_FINAL;
                    finalStartMs = (uint16_t) (millis()-beginIngressMs);
                }
                break;
            case LS_STATE_RAMPUP_FINAL: // ramping up, final
                if ( (vin - vout) < maxLoadSwitchDifferenceADCV ) {
                    state = LS_STATE_ON;
                    OCR2A = onFrequencyOCR;
                    switchOnMs = (uint16_t) (millis()-beginIngressMs);
                    return LOADSWITCH_ON;
                }
                break;
        }
    } 
    switchFailMs = (uint16_t) (millis()-beginIngressMs);
    // timed out, whats the problem ?
    TCCR2A = TCCR2A_DISABLE;
    if ( state == LS_STATE_RAMPUP ) {
        return LOADSWITCH_INRUSH_RAMP_FAILED;
    }
    return LOADSWITCH_STABLISATION_FAILED;
}
void LoadSwitch::turnOff() {
    TCCR2A = TCCR2A_DISABLE;
    OCR2A = OCR_DISABLE;

    state = LS_STATE_OFF;

}

int LoadSwitch::check() {

    // check the difference between supply and output.
    // if 
    int vin = analogRead(A0);
    int vout = analogRead(A1);
    if ( vin < minOutVoltageADCV ) {
        turnOff();
        return LOADSWITCH_LOW_VOLTAGE;
    } else if ( vin > maxSupplyVoltageADCV ) {
        turnOff();
        return LOADSWITCH_HIGH_VOLTAGE;
    }
    if ( state == LS_STATE_OFF ) {
        return LOADSWITCH_OFF;
    }
    if ( vout > minOutVoltageADCV ) {
        return LOADSWITCH_INRUSH_RAMP_FAILED;
    } else if ( (vin - vout) < maxLoadSwitchDifferenceADCV ) {
        return LOADSWITCH_STABLISATION_FAILED;
    } else {
        return LOADSWITCH_ON;
    }
}





