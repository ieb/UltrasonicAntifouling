
#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Arduino.h>


#define READBUFFER_LEN 80

#define CMD_HELP 0
#define CMD_DUMP 1
#define CMD_FREQENCY 2
#define CMD_PWM 3
#define CMD_DEADTIME 4
#define CMD_ON 5
#define CMD_OFF 6
#define CMD_PULSE 7
#define NCOMMANDS 8





class Ultrasound {
    public:
        Ultrasound(Stream * _io = &Serial);
        void begin(double frequency=20, double pwm=10, bool inverted = false);
        void process(void);
        void setFrequency(double  frequencyKhz);
        void setPwm(int percent);
        void setEnabled(bool enabled);
        void setDeadtime(int deadTimeMicros);
        void resetCounters();
    private:
        int match(const char * command, const char ** commands, int ncommands, const char ** startData);
        char * readLine();
        int8_t docmd(const char * command);
        void help();
        void dump();
        uint16_t counterTopValue = 0;
        uint16_t deadTimeTicks = 16; // 4us
        uint16_t chanALimit = 0;
        uint16_t chanBLimit = 0;
        double frequencyKhz = 0;
        double achievedFrequency = 0;
        int percent = 0;
        bool enable = false;
        Stream* io;        
        int bufferPos = 0;
        char inputLine[READBUFFER_LEN];

};



#endif