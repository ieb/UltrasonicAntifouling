#include <Arduino.h>
#include <ultrasound.h>

Ultrasound ultrasound(&Serial);


void setup() {
  Serial.begin(115200);
  Serial.println(F("Starting PWM"));
  ultrasound.begin();
  Serial.println(F("Ready"));
  Serial.println(F("$>"));

}

void loop() {
  ultrasound.process();
}