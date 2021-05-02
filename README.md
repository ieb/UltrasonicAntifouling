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

# Output screenshots

These are for a inverting driver, see Ultrasound.begin() for details on how to generate non invertig output.


![50KHz 100% PWM 2us deadtime](images/50Khz100pwm2dead.png)

![50KHz 50% PWM 2us deadtime](images/50Khz50pwm2dead.png)

![200KHz 100% PWM 1us deadtime](images/200Khz100pwm1dead.png)

# Driver and code

The driver is derived from the Jaycar circuit which uses a 5V PIC to drive the IRF540N mosfets directly. Instead this uses a RFP50N06 and a MCP14E4 dual 4.5A Mosfet driver capable of driving the gate(2200pf) of the Mosfet in about 15ns using guidance from Microchip design notes. Ramp on scopes confirms this. I found IRF540Ns are not robust enough to be driven with a clean 12v square wave. Output is upto 700v peak to peak. I get minimal ringing in the mosfet drive or the mosfet output with this setup and the high voltage output even looks like a clean sie wave at some frequencies.

Running the Arduino connected to a computer over serial port is not advised with the output enabled.

# Sequence

I found with the previous 6 chanel versiom that although I had an elaborate configurtion method over serial, I never used it, and connecting a usb port to this board without proper isolation potentially exposes the computer to 600V or more if something goes wrong. So I hard code the sequence and flash the pro mini to make change with the power side of the driver disabled.

The sequence 12 10ms bursts seperated by 20ms pause to rechage the capacitors. The sequence repeats 20 times before pausing, with a 400ms delay between sequences. Each sequence incresaes the frequency by 1.0721 times. At 80Khz, 62KHz is subtracted and the process continues. This ensures every frequency is covered.  On pause power levels are checked. On high power (> 13.7v supply) the pause is 8s. on Low power  (< 12v) the pause is 30s and below 12v the chip sleeps for 60 before checking the voltage again. No output is generated below 12v.

# LEDS

The onboard led flashes to indicate state. Flash period is 200ms.

7 flashes indicates a boot sequence.
3 flashes before sleeping for 60s
2 flashes every 5s during low power sleep for low power mode.

During operation the led toggle as the frequency changes.

