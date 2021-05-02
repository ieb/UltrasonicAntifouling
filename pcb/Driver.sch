EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Driver-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ArdinoMinPro U1
U 1 1 6081B080
P 2350 1650
F 0 "U1" H 2650 1650 60  0000 C CNN
F 1 "ArdinoMinPro" H 2350 1650 60  0000 C CNN
F 2 "Divers:ArduinoProMini" H 2650 1650 60  0001 C CNN
F 3 "" H 2650 1650 60  0001 C CNN
	1    2350 1650
	1    0    0    -1  
$EndComp
$Comp
L MCP14E3 U2
U 1 1 6081B464
P 5850 2800
F 0 "U2" H 5900 3000 60  0000 C CNN
F 1 "MCP14E4" H 5900 3000 60  0000 C CNN
F 2 "Housings_DIP:DIP-8_W7.62mm_LongPads" H 5900 3000 60  0001 C CNN
F 3 "" H 5900 3000 60  0001 C CNN
	1    5850 2800
	1    0    0    -1  
$EndComp
$Comp
L IRF540N Q1
U 1 1 6081B4AA
P 8250 2250
F 0 "Q1" H 8250 2102 40  0000 R CNN
F 1 "RPF60N06" H 8250 2399 40  0000 R CNN
F 2 "TO_SOT_Packages_THT:TO-220_Vertical" H 8071 2351 29  0000 C CNN
F 3 "" H 8250 2250 60  0000 C CNN
	1    8250 2250
	1    0    0    -1  
$EndComp
$Comp
L IRF540N Q2
U 1 1 6081B4D5
P 8250 3000
F 0 "Q2" H 8250 2852 40  0000 R CNN
F 1 "RPF60N06" H 8250 3149 40  0000 R CNN
F 2 "TO_SOT_Packages_THT:TO-220_Vertical" H 8071 3101 29  0000 C CNN
F 3 "" H 8250 3000 60  0000 C CNN
	1    8250 3000
	1    0    0    -1  
$EndComp
Text GLabel 4900 2500 0    60   Input ~ 0
PWMB
Text GLabel 4900 2350 0    60   Input ~ 0
PWMA
Text GLabel 950  2300 0    60   Output ~ 0
PWMB
Text GLabel 3900 2300 2    60   Output ~ 0
PWMA
Text GLabel 4900 3100 0    60   Input ~ 0
ENPWM
Text GLabel 3900 2200 2    60   Output ~ 0
ENPWM
$Comp
L CAPAPOL C7
U 1 1 6081B5A9
P 6250 1650
F 0 "C7" H 6300 1750 40  0000 L CNN
F 1 "1uF" H 6300 1550 40  0000 L CNN
F 2 "Capacitors_SMD:C_1210_HandSoldering" H 6350 1500 30  0001 C CNN
F 3 "" H 6250 1650 300 0000 C CNN
	1    6250 1650
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 6081B5EC
P 6650 1650
F 0 "C8" H 6650 1750 40  0000 L CNN
F 1 "100nF" H 6656 1565 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6688 1500 30  0001 C CNN
F 3 "" H 6650 1650 60  0000 C CNN
	1    6650 1650
	1    0    0    -1  
$EndComp
Text GLabel 7750 1350 2    60   Input ~ 0
12vPower
$Comp
L GND #PWR01
U 1 1 6081B682
P 6450 2000
F 0 "#PWR01" H 6450 2000 30  0001 C CNN
F 1 "GND" H 6450 1930 30  0001 C CNN
F 2 "" H 6450 2000 60  0001 C CNN
F 3 "" H 6450 2000 60  0001 C CNN
	1    6450 2000
	1    0    0    -1  
$EndComp
Text GLabel 9050 2500 0    60   Input ~ 0
12vPower
$Comp
L DIODE D3
U 1 1 60826013
P 6950 3200
F 0 "D3" H 6950 3300 40  0000 C CNN
F 1 "1N5819" H 6950 3100 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" H 6950 3200 60  0001 C CNN
F 3 "" H 6950 3200 60  0000 C CNN
	1    6950 3200
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D6
U 1 1 608260E3
P 7250 3200
F 0 "D6" H 7250 3300 40  0000 C CNN
F 1 "1N5819" H 7250 3100 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" H 7250 3200 60  0001 C CNN
F 3 "" H 7250 3200 60  0000 C CNN
	1    7250 3200
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D2
U 1 1 60826112
P 6950 2000
F 0 "D2" H 6950 2100 40  0000 C CNN
F 1 "1N5819" H 6950 1900 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" H 6950 2000 60  0001 C CNN
F 3 "" H 6950 2000 60  0000 C CNN
	1    6950 2000
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D5
U 1 1 6082614C
P 7250 2000
F 0 "D5" H 7250 2100 40  0000 C CNN
F 1 "1N5819" H 7250 1900 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" H 7250 2000 60  0001 C CNN
F 3 "" H 7250 2000 60  0000 C CNN
	1    7250 2000
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 60826327
P 7100 3850
F 0 "#PWR02" H 7100 3850 30  0001 C CNN
F 1 "GND" H 7100 3780 30  0001 C CNN
F 2 "" H 7100 3850 60  0001 C CNN
F 3 "" H 7100 3850 60  0001 C CNN
	1    7100 3850
	1    0    0    -1  
$EndComp
$Comp
L DIODE D4
U 1 1 60826392
P 7000 1350
F 0 "D4" H 7000 1450 40  0000 C CNN
F 1 "1N5819" H 7000 1250 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" H 7000 1350 60  0001 C CNN
F 3 "" H 7000 1350 60  0000 C CNN
	1    7000 1350
	-1   0    0    1   
$EndComp
Text Notes 3850 6000 0    60   ~ 0
Peak Drive current IRF540N = Q/dT = 95/39 = 2.4A \nRFP50N06 = 125/55 = 2.27A\nDriver Power\nIRF540N = 1400E-12*12*12*250E3 = 50mW\nRFP50N06 = 2200E-12*12*12*250E3 = 80mW\n\nMCP14E3 can deliver 4.5A at 18V and will drive at about 15ns for 1400pF@12V gate.\nIt will disipate 1.1W\n\nhttp://ww1.microchip.com/downloads/en/Appnotes/00799b.pdf\n\nClampin diodes on the mosfet gates mitigate latch up due too negative overshoot and protect the gate in event of positive overshoot. The test board barely overshoots.\n\n\nPro Minis will not run on 14V and are liable to blow, so stepping down to 8v with a 1A 7808\nreduces this risk and provides better isplation from the mosfets, coil and driver.\n\nThe MCP14E4 sinks no more than 1mA per input pin, so the 120R limit the output of the Pro mini to 4mA in the event of a failiure on the MCP14E4\n\n\n\n
Text GLabel 4850 6200 2    60   Output ~ 0
12vPower
$Comp
L CAPAPOL C2
U 1 1 60827661
P 3750 6600
F 0 "C2" H 3800 6700 40  0000 L CNN
F 1 "4700uF 50V" H 3800 6500 40  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D22_L41_P10" H 3850 6450 30  0001 C CNN
F 3 "" H 3750 6600 300 0000 C CNN
	1    3750 6600
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 608276BA
P 4550 6600
F 0 "C5" H 4550 6700 40  0000 L CNN
F 1 "470nF" H 4556 6515 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4588 6450 30  0001 C CNN
F 3 "" H 4550 6600 60  0000 C CNN
	1    4550 6600
	1    0    0    -1  
$EndComp
$Comp
L CAPAPOL C3
U 1 1 6082773F
P 4200 6600
F 0 "C3" H 4250 6700 40  0000 L CNN
F 1 "330uF 50v" H 4250 6500 40  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D8_L11.5_P3.5" H 4300 6450 30  0001 C CNN
F 3 "" H 4200 6600 300 0000 C CNN
	1    4200 6600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 60827B35
P 4200 7250
F 0 "#PWR03" H 4200 7250 30  0001 C CNN
F 1 "GND" H 4200 7180 30  0001 C CNN
F 2 "" H 4200 7250 60  0001 C CNN
F 3 "" H 4200 7250 60  0001 C CNN
	1    4200 7250
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 6082862A
P 2000 6200
F 0 "D1" H 2000 6300 40  0000 C CNN
F 1 "1N5819" H 2000 6100 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" H 2000 6200 60  0001 C CNN
F 3 "" H 2000 6200 60  0000 C CNN
	1    2000 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 60828980
P 2100 6650
F 0 "#PWR04" H 2100 6650 30  0001 C CNN
F 1 "GND" H 2100 6580 30  0001 C CNN
F 2 "" H 2100 6650 60  0001 C CNN
F 3 "" H 2100 6650 60  0001 C CNN
	1    2100 6650
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 60828DD8
P 4100 1500
F 0 "C6" H 4100 1600 40  0000 L CNN
F 1 "1uF" H 4106 1415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4138 1350 30  0001 C CNN
F 3 "" H 4100 1500 60  0000 C CNN
	1    4100 1500
	1    0    0    -1  
$EndComp
$Comp
L FUSE F1
U 1 1 6082914C
P 1400 6200
F 0 "F1" H 1500 6250 40  0000 C CNN
F 1 "FUSE" H 1300 6150 40  0000 C CNN
F 2 "Fuse_Holders_and_Fuses:BladeFuse-CarType" H 1400 6200 60  0001 C CNN
F 3 "" H 1400 6200 60  0000 C CNN
	1    1400 6200
	1    0    0    -1  
$EndComp
Text GLabel 3300 5150 2    60   Output ~ 0
8v
$Comp
L GND #PWR05
U 1 1 608295F1
P 3450 1400
F 0 "#PWR05" H 3450 1400 30  0001 C CNN
F 1 "GND" H 3450 1330 30  0001 C CNN
F 2 "" H 3450 1400 60  0001 C CNN
F 3 "" H 3450 1400 60  0001 C CNN
	1    3450 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 608297DC
P 3900 1850
F 0 "#PWR06" H 3900 1850 30  0001 C CNN
F 1 "GND" H 3900 1780 30  0001 C CNN
F 2 "" H 3900 1850 60  0001 C CNN
F 3 "" H 3900 1850 60  0001 C CNN
	1    3900 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 60829891
P 2350 2900
F 0 "#PWR07" H 2350 2900 30  0001 C CNN
F 1 "GND" H 2350 2830 30  0001 C CNN
F 2 "" H 2350 2900 60  0001 C CNN
F 3 "" H 2350 2900 60  0001 C CNN
	1    2350 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 608298DB
P 950 1550
F 0 "#PWR08" H 950 1550 30  0001 C CNN
F 1 "GND" H 950 1480 30  0001 C CNN
F 2 "" H 950 1550 60  0001 C CNN
F 3 "" H 950 1550 60  0001 C CNN
	1    950  1550
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 60829B76
P 1650 3350
F 0 "R1" V 1730 3350 40  0000 C CNN
F 1 "100K" V 1657 3351 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1580 3350 30  0001 C CNN
F 3 "" H 1650 3350 30  0000 C CNN
	1    1650 3350
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 60829BF5
P 1650 4050
F 0 "R2" V 1730 4050 40  0000 C CNN
F 1 "22K" V 1657 4051 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1580 4050 30  0001 C CNN
F 3 "" H 1650 4050 30  0000 C CNN
	1    1650 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 60829C58
P 1650 4500
F 0 "#PWR09" H 1650 4500 30  0001 C CNN
F 1 "GND" H 1650 4430 30  0001 C CNN
F 2 "" H 1650 4500 60  0001 C CNN
F 3 "" H 1650 4500 60  0001 C CNN
	1    1650 4500
	1    0    0    -1  
$EndComp
Text GLabel 1000 3050 0    60   Input ~ 0
12v
$Comp
L C C1
U 1 1 60829D1D
P 1400 4050
F 0 "C1" H 1400 4150 40  0000 L CNN
F 1 "100nF" H 1406 3965 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1438 3900 30  0001 C CNN
F 3 "" H 1400 4050 60  0000 C CNN
	1    1400 4050
	1    0    0    -1  
$EndComp
Text GLabel 2000 3700 2    60   Output ~ 0
ADC1
Text GLabel 3400 1900 2    60   Input ~ 0
ADC1
NoConn ~ 3150 1400
NoConn ~ 3150 1500
NoConn ~ 3150 1600
NoConn ~ 3150 1700
NoConn ~ 3150 1800
NoConn ~ 3150 2000
NoConn ~ 3150 2100
NoConn ~ 3150 2400
NoConn ~ 3150 2500
NoConn ~ 1650 2500
NoConn ~ 1650 2400
NoConn ~ 1650 2200
NoConn ~ 1650 2100
NoConn ~ 1650 2000
NoConn ~ 1650 1800
NoConn ~ 1650 1300
NoConn ~ 2450 1650
NoConn ~ 1650 1700
NoConn ~ 1650 1900
NoConn ~ 1650 1200
NoConn ~ 1650 1400
NoConn ~ 2200 800 
NoConn ~ 2300 800 
NoConn ~ 2400 800 
NoConn ~ 2500 800 
NoConn ~ 2600 800 
NoConn ~ 2700 800 
Text Notes 7250 6750 0    60   ~ 0
Ultrasound Driver
$Comp
L CONN_2 P1
U 1 1 6082AEB0
P 10600 2500
F 0 "P1" V 10550 2500 40  0000 C CNN
F 1 "CONN_2" V 10650 2500 40  0000 C CNN
F 2 "Connect:AK300-2" H 10600 2500 60  0001 C CNN
F 3 "" H 10600 2500 60  0001 C CNN
	1    10600 2500
	1    0    0    -1  
$EndComp
Text Notes 6350 1100 0    60   ~ 0
To dedicate capacitors to Mosfet driver
$Comp
L CAPAPOL C4
U 1 1 6082B568
P 3000 5500
F 0 "C4" H 3050 5600 40  0000 L CNN
F 1 "100uF" H 3050 5400 40  0000 L CNN
F 2 "Capacitors_SMD:C_1210_HandSoldering" H 3100 5350 30  0001 C CNN
F 3 "" H 3000 5500 300 0000 C CNN
	1    3000 5500
	1    0    0    -1  
$EndComp
Text Notes 4850 6450 0    60   ~ 0
Protect 12v input from freqhencies generated by driver
Text Notes 7300 3450 0    60   ~ 0
Latchup protection
Text Notes 7350 3900 0    60   ~ 0
Must be low impedance GND (latchup, parasitic npn)
$Comp
L CONN_2 P2
U 1 1 6082CEFB
P 650 6300
F 0 "P2" V 600 6300 40  0000 C CNN
F 1 "CONN_2" V 700 6300 40  0000 C CNN
F 2 "Connect:AK300-2" H 650 6300 60  0001 C CNN
F 3 "" H 650 6300 60  0001 C CNN
	1    650  6300
	-1   0    0    1   
$EndComp
$Comp
L ETD29 T1
U 1 1 6082D7AE
P 9650 2500
F 0 "T1" H 9650 2750 70  0000 C CNN
F 1 "ETD29" H 9650 2200 70  0000 C CNN
F 2 "Transformers_SMPS_ThroughHole:ETD29_13Pin_Horizontal_EPCOS-B66359A1013T" H 9650 2500 60  0001 C CNN
F 3 "" H 9650 2500 60  0000 C CNN
	1    9650 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1350 6800 1350
Wire Wire Line
	5850 1350 5850 1900
Wire Wire Line
	6250 1450 6250 1350
Connection ~ 6250 1350
Wire Wire Line
	6650 1350 6650 1450
Connection ~ 6650 1350
Wire Wire Line
	6250 1850 6250 1900
Wire Wire Line
	6250 1900 6650 1900
Wire Wire Line
	6650 1900 6650 1850
Wire Wire Line
	6450 2000 6450 1900
Connection ~ 6450 1900
Wire Wire Line
	7050 2350 7450 2350
Wire Wire Line
	7450 2350 7450 2300
Wire Wire Line
	7450 2300 8050 2300
Wire Wire Line
	6900 2500 7450 2500
Wire Wire Line
	7450 2500 7450 3050
Wire Wire Line
	7450 3050 8050 3050
Wire Wire Line
	8350 2450 8350 2550
Wire Wire Line
	8350 2550 8700 2550
Wire Wire Line
	8700 2550 8700 3300
Wire Wire Line
	8700 3300 8350 3300
Wire Wire Line
	8350 3300 8350 3200
Wire Wire Line
	8350 2800 8350 2700
Wire Wire Line
	8350 2700 9250 2700
Wire Wire Line
	8350 2050 8350 1950
Wire Wire Line
	8350 1950 8900 1950
Wire Wire Line
	8900 1950 8900 2300
Wire Wire Line
	8900 2300 9250 2300
Wire Wire Line
	9050 2500 9250 2500
Connection ~ 8500 3300
Wire Wire Line
	4900 2350 5100 2350
Wire Wire Line
	4900 2500 5100 2500
Wire Wire Line
	4900 3100 5000 3100
Wire Wire Line
	5000 3000 5000 3150
Wire Wire Line
	5000 3000 5100 3000
Wire Wire Line
	5000 3150 5100 3150
Connection ~ 5000 3100
Wire Wire Line
	6950 2200 6950 3000
Connection ~ 6950 2500
Wire Wire Line
	7250 2200 7250 3000
Connection ~ 7250 2350
Wire Wire Line
	6950 1800 6950 1650
Wire Wire Line
	6950 1650 7250 1650
Wire Wire Line
	7250 1350 7250 1800
Wire Wire Line
	6950 3400 6950 3600
Wire Wire Line
	6950 3600 7250 3600
Wire Wire Line
	7250 3600 7250 3400
Connection ~ 7100 3600
Wire Wire Line
	7200 1350 7750 1350
Connection ~ 7250 1350
Connection ~ 7250 1650
Wire Wire Line
	2200 6200 4850 6200
Wire Wire Line
	3750 6400 3750 6200
Connection ~ 3750 6200
Wire Wire Line
	4200 6400 4200 6200
Connection ~ 4200 6200
Wire Wire Line
	4550 6400 4550 6200
Connection ~ 4550 6200
Wire Wire Line
	4550 7050 4550 6800
Wire Wire Line
	3750 7050 4550 7050
Wire Wire Line
	3750 7050 3750 6800
Wire Wire Line
	4200 6800 4200 7250
Connection ~ 4200 7050
Wire Wire Line
	1000 6400 2100 6400
Wire Wire Line
	2100 6400 2100 6650
Wire Wire Line
	1800 6200 1650 6200
Wire Wire Line
	1000 6200 1150 6200
Wire Wire Line
	3450 1400 3450 1300
Wire Wire Line
	3450 1300 3150 1300
Wire Wire Line
	1650 1500 950  1500
Wire Wire Line
	950  1500 950  1550
Wire Wire Line
	1650 2300 1450 2300
Wire Wire Line
	3150 2300 3400 2300
Wire Wire Line
	2350 2900 2350 2800
Wire Wire Line
	1000 3050 1650 3050
Wire Wire Line
	1650 3050 1650 3100
Wire Wire Line
	1650 3600 1650 3800
Wire Wire Line
	1400 3850 1400 3700
Wire Wire Line
	1400 3700 2000 3700
Connection ~ 1650 3700
Wire Wire Line
	1400 4250 1400 4400
Wire Wire Line
	1400 4400 1650 4400
Wire Wire Line
	1650 4300 1650 4500
Connection ~ 1650 4400
Wire Wire Line
	3400 1900 3150 1900
Wire Wire Line
	10250 2600 10100 2600
Wire Wire Line
	10100 2600 10100 2700
Wire Wire Line
	10100 2700 10050 2700
Wire Wire Line
	10050 2300 10100 2300
Wire Wire Line
	10100 2300 10100 2400
Wire Wire Line
	10100 2400 10250 2400
Wire Wire Line
	3150 1200 4350 1200
Wire Wire Line
	4100 1200 4100 1300
Wire Wire Line
	3700 1200 3700 1300
Connection ~ 3700 1200
Wire Wire Line
	3700 1700 3700 1750
Wire Wire Line
	3700 1750 4100 1750
Wire Wire Line
	4100 1750 4100 1700
Wire Wire Line
	3900 1850 3900 1750
Connection ~ 3900 1750
Wire Wire Line
	8500 3750 8500 3300
Wire Wire Line
	5900 3750 8500 3750
Wire Wire Line
	7100 3600 7100 3850
Connection ~ 7100 3750
Wire Wire Line
	5900 3450 5900 3750
Wire Wire Line
	6900 2500 6900 2350
Wire Wire Line
	6900 2350 6650 2350
Wire Wire Line
	7050 2350 7050 2450
Wire Wire Line
	7050 2450 6800 2450
Wire Wire Line
	6800 2450 6800 2500
Wire Wire Line
	6800 2500 6650 2500
NoConn ~ 1650 1600
Wire Wire Line
	3150 2200 3400 2200
$Comp
L R R?
U 1 1 608EDC7D
P 3650 2200
F 0 "R?" V 3730 2200 40  0000 C CNN
F 1 "120R" V 3657 2201 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3580 2200 30  0001 C CNN
F 3 "" H 3650 2200 30  0000 C CNN
	1    3650 2200
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 608EE08C
P 3650 2300
F 0 "R?" V 3730 2300 40  0000 C CNN
F 1 "120R" V 3657 2301 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3580 2300 30  0001 C CNN
F 3 "" H 3650 2300 30  0000 C CNN
	1    3650 2300
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 608EE1F0
P 1200 2300
F 0 "R?" V 1280 2300 40  0000 C CNN
F 1 "120R" V 1207 2301 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1130 2300 30  0001 C CNN
F 3 "" H 1200 2300 30  0000 C CNN
	1    1200 2300
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 608EE4DB
P 3700 1500
F 0 "C?" H 3700 1600 40  0000 L CNN
F 1 "100nF" H 3706 1415 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3738 1350 30  0001 C CNN
F 3 "" H 3700 1500 60  0000 C CNN
	1    3700 1500
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 608EE669
P 1800 5450
F 0 "C?" H 1800 5550 40  0000 L CNN
F 1 "100nF" H 1806 5365 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1838 5300 30  0001 C CNN
F 3 "" H 1800 5450 60  0000 C CNN
	1    1800 5450
	1    0    0    -1  
$EndComp
Text GLabel 4350 1200 2    60   Input ~ 0
8v
Connection ~ 4100 1200
$Comp
L DIODE D?
U 1 1 608EF18D
P 1450 5150
F 0 "D?" H 1450 5250 40  0000 C CNN
F 1 "1N5819" H 1450 5050 40  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM7mm" H 1450 5150 60  0001 C CNN
F 3 "" H 1450 5150 60  0000 C CNN
	1    1450 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 5150 1100 6200
Connection ~ 1100 6200
$Comp
L LM7808ACT U?
U 1 1 608EF2FC
P 2350 5200
F 0 "U?" H 2150 5400 40  0000 C CNN
F 1 "LM7808ACT" H 2350 5400 40  0000 L CNN
F 2 "TO-220" H 2350 5300 30  0000 C CIN
F 3 "" H 2350 5200 60  0000 C CNN
	1    2350 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 5150 3300 5150
Wire Wire Line
	3000 5300 3000 5150
Connection ~ 3000 5150
Wire Wire Line
	1650 5150 1950 5150
Wire Wire Line
	1800 4800 1800 5250
Connection ~ 1800 5150
Wire Wire Line
	2350 5450 2350 5950
Wire Wire Line
	1800 5800 3000 5800
Wire Wire Line
	1800 5800 1800 5650
Wire Wire Line
	3000 5800 3000 5700
Connection ~ 2350 5800
$Comp
L GND #PWR?
U 1 1 608EFDD5
P 2350 5950
F 0 "#PWR?" H 2350 5950 30  0001 C CNN
F 1 "GND" H 2350 5880 30  0001 C CNN
F 2 "" H 2350 5950 60  0001 C CNN
F 3 "" H 2350 5950 60  0001 C CNN
	1    2350 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 5150 1250 5150
Text GLabel 1950 4800 2    60   Output ~ 0
12v
Wire Wire Line
	1800 4800 1950 4800
$EndSCHEMATC
