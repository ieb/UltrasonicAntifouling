#include <Arduino.h>
#include <ultrasound.h>


Ultrasound ultrasound(&Serial);

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


void setup() {
  Serial.begin(115200);
  Serial.println(F("Starting PWM"));
  ultrasound.begin(20,10,false);
  Serial.println(F("Ready"));
  Serial.println(F("$>"));
  toggleLed(15);

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
    double  supplyVoltage = 0.33+supplyVoltageReading*0.02738839286;  // 12.27 == 448 measured 12.6 0.33v drop
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
       return;
    } else if ( supplyVoltageReading < 489 ) { // 13.7
      Serial.println("On battery, half power");
      for (int i = 0; i < 6; i++) {
        // low power mode, rest for 30s
        // but flash the led on off to indicate resting.
        toggleLed(4);
        delay(5000);
      }
    } else {  // > 13.7
      Serial.println("On supply, full power");
      delay(5000);
    }
    rest = 0;
  }


  rest++;

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