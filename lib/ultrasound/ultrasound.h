
#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Arduino.h>


#define READBUFFER_LEN 80

#define CMD_HELP 0
#define CMD_DUMP 1
#define CMD_FREQENCY 2
#define CMD_PWM 3
#define CMD_DEADTIME 4
#define NCOMMANDS 5





class Ultrasound {
    public:
        Ultrasound(Stream * _io = &Serial);
        void begin(void);
        void process(void);
    private:
        void setFrequency(double  frequencyKhz);
        void setPwm(int percent);
        void setDeadtime(int deadTimeMicros);
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
        Stream* io;        
        int bufferPos = 0;
        char inputLine[READBUFFER_LEN];

};



#endif