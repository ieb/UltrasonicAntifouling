# Variable Frequency Ultrasound generator

This code generated 2 complementary square waves to drive MOSFETS to produce untrasound output. It will operate from about 200Hz to 250KHz with PWM 0-100% and deadtime control in microseconds.

It uses that standard Arduino PWM output, using the 16 bit timer 1 in mode 8 (see http://ww1.microchip.com/downloads/en/DeviceDoc/en590320.pdf) which is Phase Correct, frequency correct. The prescalar is set to 1 so the counter operates at 16MHz (Uno 5v, 16MHz). The counter counts up from 0 to the TOP value (in register ICR1) and down to zero again. 

Setup of the PWM is controlled by the registers

        TCCR1A = (TCCR1A & 0x0F) | 0xB0 ; // set pin 10 inverted  and pin 9 normal ie 0b1011xxxx
        TCCR1A = (TCCR1A & 0xFC) | 0x00 ; // phase correct pwm, mode 8, ie 0bxxxxxx00
        TCCR1B = (TCCR1B & 0xE7) | 0x10 ; // phase correct pwm, mode 8, ie 0bxxx10xxx

        TCCR1B = (TCCR1B & 0x0F8) | 0x01 ; // full speed 16MHz clock 0bxxxx001 = 16MHz 


Frequency = 16MHz/1/(2*ICR1) since the counter has to count up and down for each period of output. 

The tigger value of channel A (pin 9) is set to set digital to low at greater than a threashold value and the trigger value of channel B (pin 10) is set to set digital low below a value. As the counter ramps up channel B is turned off and after the dead time ticks have passed challen A is turned on.  Deadtime is equally spaced arround the TOP/2.  

The levels can be calculated as follows


        uint16_t deadTimeTicks = deadTimeMicros*8; // 16MHz clock, deadTimeTicks is from center so /2

        uint16_t counterTopValue = (uint16_t)(16000.0/(2*frequencyKhz));

        uint16_t center = counterTopValue/2;
        OCR1A = counterTopValue-((center-deadTimeTicks)*percent)/100;
        OCR1B = ((center-deadTimeTicks)*percent)/100;



The output needs to be fed into an inverting mosfet driver drivng a pair of mosfets driving a center tapped coil with all the normal protections. Deadtime need to be calculated based on the inductance of the coil to ensure the mostfets switch off correctly between pulses.

Output screenshots



![50KHz 100% PWM 2us deadtime](images/50Khz100pwm2dead.png)

![50KHz 50% PWM 2us deadtime](images/50Khz50pwm2dead.png)

![200KHz 100% PWM 1us deadtime](images/200Khz100pwm1dead.png)