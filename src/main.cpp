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
    double  supplyVoltage = supplyVoltageReading*0.02738839286;  // 12.27 == 448 measured 
    Serial.print("vr=");
    Serial.print(supplyVoltageReading);
    Serial.print(" v=");
    Serial.println(supplyVoltage);
    // engine or solar or 240v supply, when on shore power independent supply is used.
    // relay switches over.
    if ( supplyVoltageReading < 426  ) { // < 12.0
       Serial.println("Voltage too low, sleeping for 60s");
       toggleLed(6);
       delay(60000);
       checkLoadSwitch(loadswitch.turnOn());
       return;
    } else if ( supplyVoltageReading < 489 ) { // 13.7
      Serial.println("On battery, half power");
      for (int i = 0; i < 6; i++) {
        // low power mode, rest for 30s
        // but flash the led on off to indicate resting.
        toggleLed(4);
        delay(5000);
        checkLoadSwitch(loadswitch.turnOn());
      }
      loadswitch.turnOn();
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
    pulseDuration = 7;
    rechargeDuration = 20;
  } 
  for (int i = 0; i < 12; i++) {
    ultrasound.setEnabled(true);
    delay(pulseDuration);
    ultrasound.setEnabled(false);
    delay(rechargeDuration);
  }
}