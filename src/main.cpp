#include <Arduino.h>
#include <ultrasound.h>
#include <loadswitch.h>


Ultrasound ultrasound(&Serial);
LoadSwitch loadswitch(&Serial);

void toggleLed(int times) {
  static uint8_t ledOn = 0;
  ledOn = !ledOn;
  digitalWrite(LED_BUILTIN, ledOn);
  for (int i = 1; i < times; i++ ) {
    ledOn = !ledOn;
    delay(100);
    digitalWrite(LED_BUILTIN, ledOn);
  }
}

void flashLed(int flashes) {
    for (int i = 0; i < flashes; i++ ) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
    }
}

void errorSequence(int flashes, bool forever ) {
  for(int i = 0; forever && i < 10; i++) {
    flashLed(flashes);
    delay(500);
  }
}

bool checkLoadSwitch(int result, bool abort = false) {
  switch(result) {
    case LOADSWITCH_HIGH_VOLTAGE:
      errorSequence(4, abort);
      break;
    case LOADSWITCH_INRUSH_RAMP_FAILED:
      errorSequence(5, abort);
      break;
    case LOADSWITCH_STABLISATION_FAILED:
      errorSequence(6, abort);
      break;
    case LOADSWITCH_OFF:
      errorSequence(7, abort);
      break;
    case LOADSWITCH_LOW_VOLTAGE:
      flashLed(8);
      break;
    case LOADSWITCH_ON:
      return true;
  }
  return false;

}


void setup() {
  Serial.begin(115200);
  Serial.println(F("Starting PWM"));
  ultrasound.begin(12, 20,10,false);
  Serial.println(F("Ready"));
  Serial.println(F("$>"));
  loadswitch.begin(0.5,20);
  loadswitch.setSupplyVoltages(12.0,15.0);
  loadswitch.setOutputVoltage(10.5, 2.0);
  checkLoadSwitch(loadswitch.turnOn(), true);
}


// NTCLG100E2 10K
int16_t tcurveNTCLG100E2[] = {
  783, //0C = 1024*32554/(32554+10000)
  734, //5C = 1024*25339/(25339+10000)
  681, //10C =  1024*19872/(19872+10000)
  625, //15C 1024*15698/(15698+10000)
  568, //20 1024*12488/(12488+10000)
  512, //25 1024*10000/(10000+10000)
  456, //30 1024*8059/(8059+10000)
  404, //35 1024*6535/(6535+10000)
  356, //40 1024*5330/(5330+10000)
  311, //45 1024*4372/(4372+10000)
  271, //50 1024*3605/(3605+10000)
  235, //55 1024*2989/(2989+10000)
  204 //60 1024*2490/(2490+10000)
};

int16_t tcurveNMF5210K[] = {
  930, //0C = 1024*98960/(98960+10000)
  736, //5C = 1024*25580/(25580+10000)
  682, //10C =  1024*20000/(20000+10000)
  626, //15C 1024*15760/(15760+10000)
  569, //20 1024*12510/(12510+10000)
  512, //25 1024*10000/(10000+10000)
  456, //30 1024*8048/(8048+10000)
  404, //35 1024*6518/(6518+10000)
  355, //40 1024*5312/(5312+10000)
  310, //45 1024*4354/(4354+10000)
  270, //50 1024*3588/(3588+10000)
  235, //55 1024*2989/(2989+10000)
  203 //60 1024*2476/(2476+10000)
};

#define tcurve tcurveNTCLG100E2


int8_t ntcTemperature(int16_t reading) {
  if ( reading > tcurve[0] ) {
    return 0;
  }
  for (int i = 1; i < 13; i++) {
    if ( reading > tcurve[i] ) {
      return (i*5)+((tcurve[i-1]-reading)*5)/(tcurve[i-1]-tcurve[i]);
    }
  }
  return 60;
}


void loop() {
  static double frequency = 18;
  static int pwm = 20;
  static int pulse = 10;
  static int rest = 20;
  // not safe to use serial line when running with full voltage.
  // ultrasound.process();
  delay(400);
  
  if (rest == 20) {
    int16_t supplyVoltageReading = analogRead(A0);
    int16_t temperatureReading = analogRead(A2); 
    double  supplyVoltage = supplyVoltageReading*0.02738839286;  // 12.27 == 448 measured 
    int8_t temperature = ntcTemperature(temperatureReading);
    Serial.print("vr=");
    Serial.print(supplyVoltageReading);
    Serial.print(" v=");
    Serial.println(supplyVoltage);
    Serial.print("vr=");
    Serial.print(temperatureReading);
    Serial.print(" t=");
    Serial.println(temperature);

    // engine or solar or 240v supply, when on shore power independent supply is used.
    // relay switches over.
    if ( temperatureReading < 271 ) { // over 50C
       Serial.println("Over temperature 50C, sleeping for 5s");
       loadswitch.turnOff();
       toggleLed(20);
       delay(5000);
       return;
    } else if ( supplyVoltageReading < 426  ) { // < 12.0
       Serial.println("Voltage too low, sleeping for 5s");
       loadswitch.turnOff();
       toggleLed(6);
       delay(5000);
       return;
    } else if ( supplyVoltageReading < 489 ) { // 13.7
      Serial.println("On battery, half power");
      for (int i = 0; i < 6; i++) {
        // low power mode, rest for 30s
        // but flash the led on off to indicate resting.
        toggleLed(4);
        delay(5000);
      }
      checkLoadSwitch(loadswitch.turnOn());
    } else {  // > 13.7
      Serial.println("On supply, full power");
      delay(5000);
      loadswitch.turnOn();
    }
    rest = 0;
  }


  rest++;

  if(!checkLoadSwitch(loadswitch.check(), false)) {
    return; // voltage indicates should not output
  }

  toggleLed(1);
  frequency = frequency * 1.0721;
  if (frequency > 80) frequency = frequency-62.0;
  Serial.print("f=");Serial.print(frequency);Serial.print(" %=");Serial.print(pwm);Serial.print(" p=");
  Serial.print(pulse);Serial.println("ms");
  ultrasound.setPwm(pwm);
  ultrasound.setFrequency(frequency);
  ultrasound.resetCounters();
  int pulseDuration = 10;
  int rechargeDuration = 20;
  if ( frequency > 60 ) {
    pulseDuration = 5;
    rechargeDuration = 20;
  } 
  for (int i = 0; i < 12; i++) {
    ultrasound.setEnabled(true);
    delay(pulseDuration);
    ultrasound.setEnabled(false);
    delay(rechargeDuration);
  }
}