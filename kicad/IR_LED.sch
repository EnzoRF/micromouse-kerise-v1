EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 13
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
L KERISEv1-rescue:Q_NMOS_GSD Q2
U 1 1 57CF03B8
P 5800 4800
AR Path="/57CEFE78/57CF03B8" Ref="Q2"  Part="1" 
AR Path="/57CF2D36/57CF03B8" Ref="Q3"  Part="1" 
AR Path="/57CF03B8" Ref="Q2"  Part="1" 
F 0 "Q2" H 6100 4850 50  0000 R CNN
F 1 "IRFML8244" H 6450 4750 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6000 4900 50  0001 C CNN
F 3 "" H 5800 4800 50  0000 C CNN
	1    5800 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4800 5000 4800
$Comp
L KERISEv1-rescue:LED-RESCUE-KERISEv1 D3
U 1 1 57CF03C6
P 5900 3500
AR Path="/57CEFE78/57CF03C6" Ref="D3"  Part="1" 
AR Path="/57CF2D36/57CF03C6" Ref="D9"  Part="1" 
F 0 "D3" H 5900 3600 50  0000 C CNN
F 1 "VSLY5850" H 5950 3350 50  0000 C CNN
F 2 "kerikun11:LED-5MM_Angle" H 5900 3500 50  0001 C CNN
F 3 "" H 5900 3500 50  0000 C CNN
	1    5900 3500
	0    -1   -1   0   
$EndComp
$Comp
L power:+BATT #PWR56
U 1 1 57CF03CD
P 5900 2700
AR Path="/57CEFE78/57CF03CD" Ref="#PWR56"  Part="1" 
AR Path="/57CF2D36/57CF03CD" Ref="#PWR79"  Part="1" 
F 0 "#PWR56" H 5900 2550 50  0001 C CNN
F 1 "+BATT" H 5900 2840 50  0000 C CNN
F 2 "" H 5900 2700 50  0000 C CNN
F 3 "" H 5900 2700 50  0000 C CNN
	1    5900 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2700 5900 2800
$Comp
L KERISEv1-rescue:R R7
U 1 1 57CF03D4
P 5250 4800
AR Path="/57CEFE78/57CF03D4" Ref="R7"  Part="1" 
AR Path="/57CF2D36/57CF03D4" Ref="R18"  Part="1" 
AR Path="/57CF03D4" Ref="R7"  Part="1" 
F 0 "R7" V 5330 4800 50  0000 C CNN
F 1 "10" V 5250 4800 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5180 4800 50  0001 C CNN
F 3 "" H 5250 4800 50  0000 C CNN
	1    5250 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 4800 5500 4800
Text HLabel 5000 4800 0    60   Input ~ 0
IR_LED
Wire Wire Line
	5900 5000 5900 5300
$Comp
L KERISEv1-rescue:LED-RESCUE-KERISEv1 D2
U 1 1 57CF03DE
P 5900 3000
AR Path="/57CEFE78/57CF03DE" Ref="D2"  Part="1" 
AR Path="/57CF2D36/57CF03DE" Ref="D8"  Part="1" 
F 0 "D2" H 5900 3100 50  0000 C CNN
F 1 "VSLY5850" H 5950 2850 50  0000 C CNN
F 2 "kerikun11:LED-5MM_Angle" H 5900 3000 50  0001 C CNN
F 3 "" H 5900 3000 50  0000 C CNN
	1    5900 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5900 3200 5900 3300
$Comp
L KERISEv1:NSI45090 U7
U 1 1 57CF03E6
P 5900 4100
AR Path="/57CEFE78/57CF03E6" Ref="U7"  Part="1" 
AR Path="/57CF2D36/57CF03E6" Ref="U9"  Part="1" 
F 0 "U7" H 5600 4350 60  0000 C CNN
F 1 "NSI45090" H 5450 4250 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:TO-252-2Lead" H 5850 4600 100 0001 C CNN
F 3 "" H 5850 4600 100 0000 C CNN
	1    5900 4100
	1    0    0    -1  
$EndComp
$Comp
L KERISEv1-rescue:R R9
U 1 1 57CF03ED
P 5650 4500
AR Path="/57CEFE78/57CF03ED" Ref="R9"  Part="1" 
AR Path="/57CF2D36/57CF03ED" Ref="R20"  Part="1" 
AR Path="/57CF03ED" Ref="R9"  Part="1" 
F 0 "R9" V 5730 4500 50  0000 C CNN
F 1 "100" V 5650 4500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5580 4500 50  0001 C CNN
F 3 "" H 5650 4500 50  0000 C CNN
	1    5650 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	5900 4400 5900 4500
Connection ~ 5900 4500
Wire Wire Line
	5900 3700 5900 3800
Wire Wire Line
	5800 4500 5900 4500
Wire Wire Line
	5600 4100 5400 4100
Wire Wire Line
	5400 4100 5400 4500
Wire Wire Line
	5400 4500 5500 4500
Text Label 5900 3250 0    60   ~ 0
IR_LED_1
Text Label 5900 3750 0    60   ~ 0
IR_LED_2
Text Label 5900 4500 0    60   ~ 0
IR_LED_3
Text Notes 4450 2850 0    100  ~ 0
IR Transmitter\nKERI's Lab\n2017.11.03
$Comp
L KERISEv1-rescue:R R8
U 1 1 59FC4DF8
P 5500 5050
AR Path="/57CEFE78/59FC4DF8" Ref="R8"  Part="1" 
AR Path="/57CF2D36/59FC4DF8" Ref="R19"  Part="1" 
AR Path="/59FC4DF8" Ref="R8"  Part="1" 
F 0 "R8" V 5580 5050 50  0000 C CNN
F 1 "10k" V 5500 5050 50  0000 C CNN
F 2 "" V 5430 5050 50  0001 C CNN
F 3 "" H 5500 5050 50  0001 C CNN
	1    5500 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR57
U 1 1 59FC4E28
P 5900 5300
AR Path="/57CEFE78/59FC4E28" Ref="#PWR57"  Part="1" 
AR Path="/57CF2D36/59FC4E28" Ref="#PWR80"  Part="1" 
F 0 "#PWR57" H 5900 5050 50  0001 C CNN
F 1 "GND" H 5900 5150 50  0000 C CNN
F 2 "" H 5900 5300 50  0000 C CNN
F 3 "" H 5900 5300 50  0000 C CNN
	1    5900 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR55
U 1 1 59FC4E6D
P 5500 5300
AR Path="/57CEFE78/59FC4E6D" Ref="#PWR55"  Part="1" 
AR Path="/57CF2D36/59FC4E6D" Ref="#PWR78"  Part="1" 
F 0 "#PWR55" H 5500 5050 50  0001 C CNN
F 1 "GND" H 5500 5150 50  0000 C CNN
F 2 "" H 5500 5300 50  0000 C CNN
F 3 "" H 5500 5300 50  0000 C CNN
	1    5500 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5300 5500 5200
Wire Wire Line
	5500 4800 5500 4900
Connection ~ 5500 4800
Wire Wire Line
	5900 4500 5900 4600
Wire Wire Line
	5500 4800 5600 4800
$EndSCHEMATC
