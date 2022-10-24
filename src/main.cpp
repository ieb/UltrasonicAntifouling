#include <Arduino.h>
#include <ultrasound.h>
#include <loadswitch.h>

#define TOPF 30000
#define BOTF 15000
#define STEPF 100


const int pwm = 20;


Ultrasound ultrasound(&Serial);
LoadSwitch loadswitch(&Serial);

void changeLed() {
  static uint8_t ledOn = 0;
  ledOn = !ledOn;
  digitalWrite(LED_BUILTIN, ledOn);
}

void flashLed(int flashes) {
  digitalWrite(LED_BUILTIN, LOW);
  for (int i = 0; i < flashes; i++ ) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(400);
      digitalWrite(LED_BUILTIN, LOW);
      delay(400);
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
  Serial.begin(9600);
  Serial.println(F("Starting PWMv2"));
  ultrasound.begin(12, 20,10,false);
  Serial.println(F("Ready"));
  Serial.println(F("$>"));
  loadswitch.begin(0.5,20);
  Serial.println(F("1"));
  loadswitch.setSupplyVoltages(12.0,15.0);
  Serial.println(F("2"));
  loadswitch.setOutputVoltage(10.5, 2.0);
  Serial.println("Turning On");
  checkLoadSwitch(loadswitch.turnOn(), true);
  Serial.println("SetupDone");
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

#define tcurve tcurveNMF5210K


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



// 12 steps in each band
// 14 bands 19 - 41 Khz
// 80Hz steps at 20Khz
// 344Hz at 41Khz
// 600ms at 20Khz
// 300ms at 40Khz

void fullScan() {
  static double freq = 19000;
  uint16_t duration = 300.0+300.0*(41000.0-freq)/(41000.0-19000.0);
  Serial.print("jaycar f=");
  Serial.print(freq);
  Serial.print(" d=");
  Serial.println(duration);
  
  ultrasound.setPwm(pwm);
  ultrasound.setFrequencyHz(freq);
  ultrasound.resetCounters();
  ultrasound.setEnabled(true);
  delay(duration);
  ultrasound.setEnabled(false);
  double step = 80.0+(344.0-80.0)*(1.0-(41000.0-freq)/(41000.0-19000.0));
  freq += step;
  if (freq > 41000) {
    freq = 19000;
  }
}

  




/*
void randomPulse(uint16_t bottom=BOTF, uint16_t top=TOPF) {
  Serial.println(F("Random Pulse"));
  ultrasound.setPwm(pwm);
  for ( int i = 0; i < 10; i++) {
    ultrasound.setFrequencyHz(random(bottom,top));
    ultrasound.resetCounters();
    ultrasound.setEnabled(true);
    delay(300);
    ultrasound.setEnabled(false);
    delay(50);
  } 
}
void staticOutput(uint16_t freq, uint16_t duration) {
  Serial.print(F("Static: "));
  Serial.println(freq);
  ultrasound.setPwm(pwm);
  ultrasound.setFrequencyHz(freq);
  ultrasound.resetCounters();
  ultrasound.setEnabled(true);
  delay(duration);
  ultrasound.setEnabled(false);

}

void fixed(uint16_t bottom=BOTF, uint16_t top=TOPF) {
  Serial.print(F("Fixed Pulse: "));
  uint16_t f1 = random(bottom,top);
  Serial.println(f1);
  ultrasound.setPwm(pwm);
  ultrasound.setFrequencyHz(f1);
  ultrasound.resetCounters();
  ultrasound.setEnabled(true);
  delay(500);
  ultrasound.setEnabled(false);
}
void warble(uint16_t bottom=BOTF, uint16_t top=TOPF) {
  uint16_t f1 = random(bottom,top);
  uint16_t f2 = random(bottom,top);
  Serial.print(F("Warble Pulse"));
  Serial.print(f1);
  Serial.print(F(" "));
  Serial.println(f2);
  ultrasound.setPwm(pwm);
  ultrasound.setFrequencyHz(f1);
  ultrasound.resetCounters();
  ultrasound.setEnabled(true);
  for ( int i = 0; i < 20; i++) {
    ultrasound.setFrequencyHz(f2);
    delay(100);
    ultrasound.setFrequencyHz(f1);
    delay(100);
  } 
  ultrasound.setEnabled(false);
}
void rampUp(uint16_t bottom=BOTF, uint16_t top=TOPF, uint16_t step=STEPF) {  
  Serial.println(F("Ramp Up"));
  ultrasound.setPwm(pwm);
  ultrasound.setFrequencyHz(bottom);
  ultrasound.resetCounters();
  ultrasound.setEnabled(true);
  for ( int32_t f = bottom; f < top; f += step  ) {
    ultrasound.setFrequencyHz(f);
  } 
  ultrasound.setEnabled(false);
}
void rampDown(uint16_t bottom=BOTF, uint16_t top=TOPF, uint16_t step=STEPF) {
  Serial.println(F("Ramp Down"));
  ultrasound.setPwm(pwm);
  ultrasound.setFrequencyHz(top);
  ultrasound.resetCounters();
  ultrasound.setEnabled(true);
  for ( int32_t f = top; f > bottom; f -= step  ) {
    ultrasound.setFrequencyHz(f);
  } 
  ultrasound.setEnabled(false);
}
void fastRamp(uint16_t bottom=BOTF, uint16_t top=TOPF, uint16_t step=STEPF) {  
  Serial.println(F("Ramp UpDown"));
  ultrasound.setPwm(pwm);
  ultrasound.setFrequencyHz(bottom);
  ultrasound.resetCounters();
  ultrasound.setEnabled(true);
  for ( int i = 0; i < 5; i++) {
    for ( int32_t f = bottom; f < top; f += step*10  ) {
      ultrasound.setFrequencyHz(f);
    } 
    for ( int32_t f = top; f > bottom; f -= step*10  ) {
      ultrasound.setFrequencyHz(f);
    } 
  }
  ultrasound.setEnabled(false);
}
*/


void loop() {
//  static uint16_t freq = 20000;
  static int rest = 20;
  int delayTime = 1000;
  // not safe to use serial line when running with full voltage.
  // ultrasound.process();
  delay(400);
  
  if (rest == 20) {
    int16_t supplyVoltageReading = analogRead(A0);
    int16_t temperatureReading = analogRead(A2); 
    double  supplyVoltage = supplyVoltageReading*0.02738839286;  // 12.27 == 448 measured 
    int8_t temperature = ntcTemperature(temperatureReading);
    Serial.print(F("vr="));
    Serial.print(supplyVoltageReading);
    Serial.print(F(" v="));
    Serial.println(supplyVoltage);
    Serial.print(F("vr="));
    Serial.print(temperatureReading);
    Serial.print(F(" t="));
    Serial.println(temperature);

    // engine or solar or 240v supply, when on shore power independent supply is used.
    // relay switches over.
    if ( temperatureReading < 271 ) { // over 50C
       Serial.println(F("Over temperature 50C, sleeping for 5s"));
       loadswitch.turnOff();
       flashLed(10);
       delay(5000);
       return;
    } else if ( supplyVoltageReading < 426  ) { // < 12.0
       Serial.println(F("Voltage too low, sleeping for 5s"));
       loadswitch.turnOff();
       flashLed(3);
       delay(5000);
       return;
    } else if ( supplyVoltageReading < 489 ) { // 13.7
      Serial.println(F("On battery, half power"));
      for (int i = 0; i < 3; i++) {
        // low power mode, rest for 30s
        // but flash the led on off to indicate resting.
        flashLed(2);
        delay(5000);
      }
      checkLoadSwitch(loadswitch.turnOn());
      delayTime = 2000;
    } else {  // > 13.7
      Serial.println(F("On supply, full power"));
      delay(2000);
      loadswitch.turnOn();
      delayTime = 1000;
    }
    rest = 0;
  }


  rest++;

  if(!checkLoadSwitch(loadswitch.check(), false)) {
    return; // voltage indicates should not output
  }
  



  changeLed();



  fullScan();
  delay(delayTime);


  /*
  uint16_t lowF = 19000;
  uint16_t highF = 32000;
  uint16_t stepF = 100;

  int p = random(1,100)%8;
  p  = 6;
  if ( p == 0 ) {
    staticOutput(freq,500);
    freq += 1000;
    if (freq > 41000) freq = 20000;
  } else if ( p == 1 ) {
    randomPulse(lowF, highF);    
  } else if (p == 2) {
    rampUp(lowF, highF, stepF);
  } else if (p == 3) {
    fastRamp(lowF, highF, stepF);
  } else if (p == 4) {
    warble(lowF, highF);
  } else if (p == 5) {
    fixed(lowF, highF);
  } else if ( p == 6) {
    fullScan();
  } else {
    rampDown(lowF, highF, stepF);    
  }
  */

/*
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
  */
}