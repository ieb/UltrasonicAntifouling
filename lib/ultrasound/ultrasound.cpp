#include "ultrasound.h"




static const char * ultrasound_commands[] = {
    "help", //0
    "dump", //1
    "freq ", //2
    "pwm ", //3
    "deadtime ", // 4
    "on", // 5
    "off", // 6
    "pulse " // 7
};






Ultrasound::Ultrasound(Stream * _io) {
    io = _io;
}


void Ultrasound::begin(double frequency, double pwm, bool inverted) {
    // Timer 1 is connected to pins 9 and 10
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  
  /// hhttp://ww1.microchip.com/downloads/en/DeviceDoc/en590320.pdf 
  // page 114 for PWM description.
  // page 135

  // mode needs to set TOP and PWM.
  if (inverted) {
      TCCR1A = (TCCR1A & 0x0F) | 0xB0 ; // set pin 10 inverted ie 0b1011xxxx for MCP14E3 or  for 0b11100000 MCP14E4
  } else {
      TCCR1A = (TCCR1A & 0x0F) | 0xE0 ; // set pin 10 inverted ie 0b11100000 for MCP14E4, off is low.
  }
  TCCR1A = (TCCR1A & 0xFC) | 0x00 ; // phase correct pwm, mode 8, ie 0bxxxxxx00
  TCCR1B = (TCCR1B & 0xE7) | 0x10 ; // phase correct pwm, mode 8, ie 0bxxx10xxx

  TCCR1B = (TCCR1B & 0x0F8) | 0x01 ; // full speed 16MHz clock 0bxxxx001 = 16MHz, 0bxxxx010 = 2MHz, 0bxxxx011 = 250Khz, 0bxxxx100 = 15.625KHz 
//  TCCR1B = (TCCR1B & 0x0F8) | 0x02 ; // 2MHz
//  TCCR1B = (TCCR1B & 0x0F8) | 0x03 ; // 250KHz
//  TCCR1B = (TCCR1B & 0x0F8) | 0x04 ; // 15.625KHz 
  setEnabled(false);
  setFrequency(frequency); // 62.5Khz
  setPwm(pwm);
}

// reset counters before each cycle to ensure that
// the sequence doesnt start with a long pulse.
// which can be long enough to blow a mosfet without
// deadtime.
void Ultrasound::resetCounters() {
    cli();
    TCNT1 = 0x00;
    sei();
}

void Ultrasound::setEnabled(bool enabled) {
    enable = enabled;
    setPwm(percent);
    if ( enable ) {
        digitalWrite(11, HIGH);
    } else {
        digitalWrite(11, LOW);
    }
}


void Ultrasound::setFrequency(double requestedFrequencyKhz) {
  if ( requestedFrequencyKhz > 250 ) {
    frequencyKhz = 250; 
  } else if ( requestedFrequencyKhz < 0.2 ) {
    frequencyKhz = 0.2; 
  } else {
      frequencyKhz = requestedFrequencyKhz;
  }
  // round , but take account of the 1 extra 
  counterTopValue = (uint16_t)(16000.0/(2*frequencyKhz));
  achievedFrequency = 16000.0/(2*(counterTopValue+1));
  ICR1 = counterTopValue;
  setPwm(percent);
}

void Ultrasound::setPwm(int requestedPercent) {
  
  if (requestedPercent > 100 ) {
      percent = 100;
  } else if  (requestedPercent < 0 ) {
      percent = 0;
  } else {
    percent = requestedPercent;
  }
  uint16_t center = (counterTopValue/2);
  chanALimit = counterTopValue-((center-deadTimeTicks)*percent)/100;
  chanBLimit = ((center-deadTimeTicks)*percent)/100;
  if ( enable ) {
    OCR1A = chanALimit;
    OCR1B = chanBLimit;
  } else {
    OCR1A = counterTopValue;
    OCR1B = 0;
  }

}

void Ultrasound::setDeadtime(int deadTimeMicros) {
    deadTimeTicks = deadTimeMicros*8; // 16MHz clock, deadTimeTicks is from center so /2
    setPwm(percent);
}









void Ultrasound::help() {
    io->println(F("Lists of numbers should be comma seperated with no spaces."));
    io->println(F("Commands:"));
    io->println(F("help           - this help"));
    io->println(F("dump           - dump status"));
    io->println(F("freq <khz>     - Set the Frequency in khz (double)"));
    io->println(F("pwm <%>        - Set PWM as a percentage (int)"));
    io->println(F("deadtime <us>  - Set deadtime in us (int)"));
    io->println(F("on             - Turn output on"));
    io->println(F("off            - Turn output off"));
    io->println(F("pulse <ms>     - Turn output pn for ms"));
}



int8_t Ultrasound::docmd(const char * command) {
    const char *data;
    int cid = match(command, ultrasound_commands, NCOMMANDS, &data );

    switch(cid) {
        case CMD_HELP: 
            help(); 
            break;
        case CMD_DUMP: 
            dump(); 
            break;
        case CMD_FREQENCY:
            setFrequency(atof(data));
            io->print(F("f="));
            io->print(achievedFrequency);
            io->print(F(",t="));
            io->println(counterTopValue);
            break;
        case CMD_PWM:
            setPwm(atoi(data));
            io->print(F("a="));
            io->print(chanALimit);
            io->print(F(",b="));
            io->println(chanBLimit);
            break;
        case CMD_DEADTIME:
            setDeadtime(atoi(data));
            io->print(F("a="));
            io->print(chanALimit);
            io->print(F(",b="));
            io->print(chanBLimit);
            io->print(F(",dtt="));
            io->println(deadTimeTicks);
            break;
        case CMD_ON:
            setEnabled(true);
            break;
        case CMD_OFF:
            setEnabled(false);
            break;
        case CMD_PULSE:
            {
                int16_t duration = atoi(data);
                io->print(F("p="));
                io->print(duration);
                io->println(" on");
                setEnabled(true);
                delay(duration);
                setEnabled(false);
                io->println("off");

            }            
            break;
        default:
            io->print(F("Command Not recognised:"));
            io->println(command);
            break;

    }
    return cid;
}

        uint16_t counterTopValue = 0;
        uint16_t deadTimeTicks = 16; // 4us
        uint16_t chanALimit = 0;
        uint16_t chanBLimit = 0;
        double frequencyKhz = 0;
        double achievedFrequency = 0;
        int percent = 0;


void Ultrasound::dump() { 
    io->print(F("Requested Frequency "));
    io->println(frequencyKhz);
    io->print(F("Frequency "));
    io->println(achievedFrequency);
    io->print(F("PWM (%) "));
    io->println(percent);
    io->print(F("Counter Top Value "));
    io->println(counterTopValue);
    io->print(F("DeadTime Ticks "));
    io->println(deadTimeTicks);
    io->print(F("DeadTime Ticks (us) "));
    io->println((0.125*deadTimeTicks));
    io->print(F("Channel A Limit "));
    io->println(chanALimit);
    io->print(F("Channel B Limit "));
    io->println(chanBLimit);
}



void Ultrasound::process() {
    char * command = readLine();
    if ( command != NULL ) {
        docmd(command);
        io->print(F("$>"));
    }
}





int Ultrasound::match(const char * command, const char ** commands, int ncommands, const char ** startData) {
    
    for( int i = 0; i < ncommands; i++) {
        int len = strlen(commands[i]);
        if ( strncmp(command, commands[i], len) == 0 ) {
            *startData = &command[len];
           return i;
        }
    }
    return -1;
}





char * Ultrasound::readLine() {
  // Read lines from serial into buffer for processing.
  // 
  while(io->available() > 0) {
    char b = io->read();

    if ( b == '\n') {
      inputLine[bufferPos] = '\0';
      if (bufferPos > 0 && inputLine[bufferPos-1] == '\r') {
          inputLine[bufferPos-1] = '\0';
      }
      bufferPos = 0;
      return inputLine;
    } else if ( bufferPos < READBUFFER_LEN-1 ) {
      inputLine[bufferPos] = b;
      bufferPos++;
    } else {
      io->println(F("Error, input too long"));
      bufferPos = 0;
      return NULL;
    }
  }
  return NULL;
}

