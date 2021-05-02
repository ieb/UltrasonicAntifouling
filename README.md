
# Ultrasonic Antifouling Mk2.

My Mk1 unit finally failed after 4 years contnuous permanently on. It was only restarted when there were powercuts on shorepower. If failed because of salt getting onto the back of the board causing a short which blew the Arduino. Rather than fix, I decided to build Mk2. This time its taken 2 weeks of evenings. Last time too months.

The design is much simpler. It uses the PWM output of the Atmel328p Timer1 running off a 16MHz 5V pro mini with no pre-scaler. The MOSFET drivers are still used over driving the MOSFETs from logic levels, but there is not precise frequency generator the variable power is simplified to run in 3 states depending on input voltage. Anything over 13.7 runs at high power consumption. 13.7 to 12 at half power consumption. Below 12 the 328p goes into a sleep mode drawing 20mA until the supply voltage returns. 

This time, rather than driving 6 channels from a single Ardiono I am dedicating an Ardiono Pro Mini to each channel, and putting each in their own IP67 sealed box, with a thermally coupled external heatsink. This eliminates 600V high frequency being routed round the boat, which never felt right.

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

One anomaly that was discovered in testing, if the timer is left to run every now and again when it wraps round a super long pulse is output. This can result in not enough deadtime at which point both MOSFETS will latch up, and if there isnt a current limiting device blow them or the fuse. I used a 21w 12v bulb during testing which would light up when there was an over current event.

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

During operation the led toggles as the frequency changes.


# Output.

Output comes out at 757v peak to peak at masimum dropping off a bit at higher frequencies. The output wave is a lot cleaner and more sinusoidal than before, and the output sequence seems to generate more ultrasound for longer than before.


![Output, probably 70Khz](images/Output.png)

![Output, probably 50Khz](images/Output50KHz.png)

![Output, probably 27Khz](images/WierdOutput.png)


# Prototype

The prototype is on a double sided CNC milled PCB, which has been thourugly hacked to get the board quiet and efficient with minimal interference on supply line. Following units will have less hacked boards, and probably more surface mount components.



