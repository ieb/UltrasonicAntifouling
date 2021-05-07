
#ifndef SOFTSTART_H
#define SOFTSTART_H

#include <Arduino.h>


#define TCCR2A_ENABLE 0b00001100
#define TCCR2A_DISABLE 0x00
#define OCR_DISABLE 0xff

#define LS_STATE_OFF 0
#define LS_STATE_RAMPUP 1
#define LS_STATE_RAMPUP_FINAL 2
#define LS_STATE_ON 3


#define LOADSWITCH_OFF 0
#define LOADSWITCH_ON 1
#define LOADSWITCH_LOW_VOLTAGE 2
#define LOADSWITCH_INRUSH_RAMP_FAILED 3
#define LOADSWITCH_STABLISATION_FAILED 4
#define LOADSWITCH_HIGH_VOLTAGE 5


class LoadSwitch {
    public:
        LoadSwitch(Stream * _io = &Serial);
        void begin(int startFrequency, int runFrequency );
        int turnOn();
        int turnOff();
        int check();
        void setSupplyVoltages(double min, double max);
        void setOutputVoltage(double min, double maxDifference);
        uint16_t finalStartMs = 0;
        uint16_t switchOnMs = 0;
        uint16_t switchFailMs = 0;
    private:
        uint8_t getTimerOn(int frequencyKhz);
        Stream* io;        
        uint8_t state = LS_STATE_OFF;
        int startFrequencyOCR; // value of OCR2A register
        int onFrequencyOCR; // value of OCR2A register
        int minSupplyVoltageADCV; // value of analogRead
        int maxSupplyVoltageADCV; // value of analogRead
        int minOutVoltageADCV; // difference of analogueRead
        int maxLoadSwitchDifferenceADCV; // difference of analogueRead
        uint16_t ontimeMillis;
};



#endif