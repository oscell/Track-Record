EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 8268 11693 portrait
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
L Connector_Generic:Conn_01x03 J2
U 1 1 63FF8A67
P 5200 2050
F 0 "J2" H 5280 2092 50  0000 L CNN
F 1 "Motor_1" H 5280 2001 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 5200 2050 50  0001 C CNN
F 3 "~" H 5200 2050 50  0001 C CNN
	1    5200 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1950 4700 1950
$Comp
L power:GND #PWR012
U 1 1 63FFA5AF
P 4700 1850
F 0 "#PWR012" H 4700 1600 50  0001 C CNN
F 1 "GND" H 4705 1677 50  0000 C CNN
F 2 "" H 4700 1850 50  0001 C CNN
F 3 "" H 4700 1850 50  0001 C CNN
	1    4700 1850
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 63FFB1BC
P 4550 2050
F 0 "#PWR09" H 4550 1900 50  0001 C CNN
F 1 "+5V" H 4565 2223 50  0000 C CNN
F 2 "" H 4550 2050 50  0001 C CNN
F 3 "" H 4550 2050 50  0001 C CNN
	1    4550 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 1950 4700 1850
Wire Wire Line
	4550 2050 5000 2050
Wire Wire Line
	4550 2150 5000 2150
Text Label 4550 2150 0    50   ~ 0
Signal_1
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 63FFC819
P 5200 2800
F 0 "J3" H 5280 2842 50  0000 L CNN
F 1 "Motor_2" H 5280 2751 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 5200 2800 50  0001 C CNN
F 3 "~" H 5200 2800 50  0001 C CNN
	1    5200 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2700 4700 2700
$Comp
L power:GND #PWR013
U 1 1 63FFC86C
P 4700 2600
F 0 "#PWR013" H 4700 2350 50  0001 C CNN
F 1 "GND" H 4705 2427 50  0000 C CNN
F 2 "" H 4700 2600 50  0001 C CNN
F 3 "" H 4700 2600 50  0001 C CNN
	1    4700 2600
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 63FFC876
P 4550 2800
F 0 "#PWR010" H 4550 2650 50  0001 C CNN
F 1 "+5V" H 4565 2973 50  0000 C CNN
F 2 "" H 4550 2800 50  0001 C CNN
F 3 "" H 4550 2800 50  0001 C CNN
	1    4550 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 2700 4700 2600
Wire Wire Line
	4550 2800 5000 2800
Wire Wire Line
	4550 2900 5000 2900
Text Label 4550 2900 0    50   ~ 0
Signal_2
$Comp
L Regulator_Linear:L7805 U1
U 1 1 63FFF5D9
P 2900 2100
F 0 "U1" H 2900 2342 50  0000 C CNN
F 1 "L7805" H 2900 2251 50  0000 C CNN
F 2 "L78S05CV:TO-220-STANDING" H 2925 1950 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 2900 2050 50  0001 C CNN
	1    2900 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3450 4700 3450
$Comp
L power:GND #PWR014
U 1 1 64001F02
P 4550 3450
F 0 "#PWR014" H 4550 3200 50  0001 C CNN
F 1 "GND" H 4555 3277 50  0000 C CNN
F 2 "" H 4550 3450 50  0001 C CNN
F 3 "" H 4550 3450 50  0001 C CNN
	1    4550 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	4700 3450 4700 3350
Wire Wire Line
	4550 3550 5000 3550
$Comp
L power:+12V #PWR011
U 1 1 64004CB5
P 4700 3350
F 0 "#PWR011" H 4700 3200 50  0001 C CNN
F 1 "+12V" H 4715 3523 50  0000 C CNN
F 2 "" H 4700 3350 50  0001 C CNN
F 3 "" H 4700 3350 50  0001 C CNN
	1    4700 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 640051B9
P 2900 2550
F 0 "#PWR04" H 2900 2300 50  0001 C CNN
F 1 "GND" H 2905 2377 50  0000 C CNN
F 2 "" H 2900 2550 50  0001 C CNN
F 3 "" H 2900 2550 50  0001 C CNN
	1    2900 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 640058D3
P 3400 2000
F 0 "#PWR07" H 3400 1850 50  0001 C CNN
F 1 "+5V" H 3415 2173 50  0000 C CNN
F 2 "" H 3400 2000 50  0001 C CNN
F 3 "" H 3400 2000 50  0001 C CNN
	1    3400 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 2550 2900 2500
Wire Wire Line
	3200 2100 3400 2100
Wire Wire Line
	2600 2100 2350 2100
Wire Wire Line
	2350 2100 2350 2000
$Comp
L Device:C C1
U 1 1 64006D66
P 2350 2300
F 0 "C1" H 2465 2346 50  0000 L CNN
F 1 "0.33u" H 2465 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2388 2150 50  0001 C CNN
F 3 "~" H 2350 2300 50  0001 C CNN
	1    2350 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 64007325
P 3400 2300
F 0 "C3" H 3515 2346 50  0000 L CNN
F 1 "0.1u" H 3515 2255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3438 2150 50  0001 C CNN
F 3 "~" H 3400 2300 50  0001 C CNN
	1    3400 2300
	1    0    0    -1  
$EndComp
Connection ~ 2900 2500
Wire Wire Line
	2900 2500 2900 2400
Wire Wire Line
	2900 2500 2350 2500
Wire Wire Line
	2350 2500 2350 2450
Wire Wire Line
	2350 2150 2350 2100
Connection ~ 2350 2100
Wire Wire Line
	3400 2000 3400 2100
Connection ~ 3400 2100
Wire Wire Line
	3400 2450 3400 2500
Wire Wire Line
	3400 2500 2900 2500
Wire Wire Line
	3400 2150 3400 2100
$Comp
L Regulator_Linear:L7805 U2
U 1 1 6400FEFF
P 2900 3200
F 0 "U2" H 2900 3442 50  0000 C CNN
F 1 "L7805" H 2900 3351 50  0000 C CNN
F 2 "L78S05CV:TO-220-STANDING" H 2925 3050 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 2900 3150 50  0001 C CNN
	1    2900 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 64010031
P 2900 3650
F 0 "#PWR05" H 2900 3400 50  0001 C CNN
F 1 "GND" H 2905 3477 50  0000 C CNN
F 2 "" H 2900 3650 50  0001 C CNN
F 3 "" H 2900 3650 50  0001 C CNN
	1    2900 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3650 2900 3600
Wire Wire Line
	3200 3200 3400 3200
Wire Wire Line
	2600 3200 2350 3200
Wire Wire Line
	2350 3200 2350 3100
$Comp
L Device:C C2
U 1 1 64010053
P 2350 3400
F 0 "C2" H 2465 3446 50  0000 L CNN
F 1 "0.33u" H 2465 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2388 3250 50  0001 C CNN
F 3 "~" H 2350 3400 50  0001 C CNN
	1    2350 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 6401005D
P 3400 3400
F 0 "C4" H 3515 3446 50  0000 L CNN
F 1 "0.1u" H 3515 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3438 3250 50  0001 C CNN
F 3 "~" H 3400 3400 50  0001 C CNN
	1    3400 3400
	1    0    0    -1  
$EndComp
Connection ~ 2900 3600
Wire Wire Line
	2900 3600 2900 3500
Wire Wire Line
	2900 3600 2350 3600
Wire Wire Line
	2350 3600 2350 3550
Wire Wire Line
	2350 3250 2350 3200
Connection ~ 2350 3200
Wire Wire Line
	3400 3100 3400 3200
Connection ~ 3400 3200
Wire Wire Line
	3400 3550 3400 3600
Wire Wire Line
	3400 3600 2900 3600
Wire Wire Line
	3400 3250 3400 3200
$Comp
L power:+5VD #PWR08
U 1 1 6401311C
P 3400 3100
F 0 "#PWR08" H 3400 2950 50  0001 C CNN
F 1 "+5VD" H 3415 3273 50  0000 C CNN
F 2 "" H 3400 3100 50  0001 C CNN
F 3 "" H 3400 3100 50  0001 C CNN
	1    3400 3100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J1
U 1 1 64018309
P 4900 5300
F 0 "J1" H 4950 6417 50  0000 C CNN
F 1 "RPI3_Connector" H 4950 6326 50  0000 C CNN
F 2 "1x20_mirrored:PinSocket_2x20_P2.54mm_Vertical" H 4900 5300 50  0001 C CNN
F 3 "~" H 4900 5300 50  0001 C CNN
	1    4900 5300
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW1
U 1 1 6401D13D
P 2900 4550
F 0 "SW1" H 2900 4835 50  0000 C CNN
F 1 "Power Switch" H 2900 4744 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2900 4550 50  0001 C CNN
F 3 "~" H 2900 4550 50  0001 C CNN
	1    2900 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 6401ED36
P 5200 3550
F 0 "J4" H 5280 3592 50  0000 L CNN
F 1 "12V_connector" H 5280 3501 50  0000 L CNN
F 2 "1x20_mirrored:BarrelJack_Horizontal" H 5200 3550 50  0001 C CNN
F 3 "~" H 5200 3550 50  0001 C CNN
	1    5200 3550
	1    0    0    -1  
$EndComp
NoConn ~ 5000 3650
NoConn ~ 3100 4650
$Comp
L power:+12V #PWR03
U 1 1 640206F2
P 2500 4500
F 0 "#PWR03" H 2500 4350 50  0001 C CNN
F 1 "+12V" H 2515 4673 50  0000 C CNN
F 2 "" H 2500 4500 50  0001 C CNN
F 3 "" H 2500 4500 50  0001 C CNN
	1    2500 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2700 4550 2500 4550
Wire Wire Line
	2500 4550 2500 4500
$Comp
L power:+12VA #PWR01
U 1 1 640229C0
P 2350 2000
F 0 "#PWR01" H 2350 1850 50  0001 C CNN
F 1 "+12VA" H 2365 2173 50  0000 C CNN
F 2 "" H 2350 2000 50  0001 C CNN
F 3 "" H 2350 2000 50  0001 C CNN
	1    2350 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+12VA #PWR02
U 1 1 64022E24
P 2350 3100
F 0 "#PWR02" H 2350 2950 50  0001 C CNN
F 1 "+12VA" H 2365 3273 50  0000 C CNN
F 2 "" H 2350 3100 50  0001 C CNN
F 3 "" H 2350 3100 50  0001 C CNN
	1    2350 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+12VA #PWR06
U 1 1 640231B0
P 3300 4350
F 0 "#PWR06" H 3300 4200 50  0001 C CNN
F 1 "+12VA" H 3315 4523 50  0000 C CNN
F 2 "" H 3300 4350 50  0001 C CNN
F 3 "" H 3300 4350 50  0001 C CNN
	1    3300 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4450 3300 4450
Wire Wire Line
	3300 4450 3300 4350
Wire Wire Line
	5200 4600 5650 4600
Wire Wire Line
	5650 4600 5650 4800
$Comp
L power:GND #PWR016
U 1 1 64025C57
P 5650 4800
F 0 "#PWR016" H 5650 4550 50  0001 C CNN
F 1 "GND" H 5655 4627 50  0000 C CNN
F 2 "" H 5650 4800 50  0001 C CNN
F 3 "" H 5650 4800 50  0001 C CNN
	1    5650 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 4500 5650 4500
Wire Wire Line
	5650 4500 5650 4200
$Comp
L power:+5VD #PWR015
U 1 1 640271F7
P 5650 4200
F 0 "#PWR015" H 5650 4050 50  0001 C CNN
F 1 "+5VD" H 5665 4373 50  0000 C CNN
F 2 "" H 5650 4200 50  0001 C CNN
F 3 "" H 5650 4200 50  0001 C CNN
	1    5650 4200
	1    0    0    -1  
$EndComp
Text Label 4200 4600 0    50   ~ 0
Signal_2
Text Label 4200 4500 0    50   ~ 0
Signal_1
Wire Wire Line
	4700 4600 4200 4600
Wire Wire Line
	4700 4500 4200 4500
NoConn ~ 5200 4400
NoConn ~ 5200 4700
NoConn ~ 5200 4800
NoConn ~ 5200 4900
NoConn ~ 5200 5000
NoConn ~ 5200 5100
NoConn ~ 5200 5200
NoConn ~ 5200 5300
NoConn ~ 5200 5400
NoConn ~ 5200 5500
NoConn ~ 5200 5600
NoConn ~ 5200 5700
NoConn ~ 5200 5800
NoConn ~ 5200 5900
NoConn ~ 5200 6000
NoConn ~ 5200 6100
NoConn ~ 5200 6200
NoConn ~ 5200 6300
NoConn ~ 4700 6300
NoConn ~ 4700 6200
NoConn ~ 4700 6100
NoConn ~ 4700 6000
NoConn ~ 4700 5900
NoConn ~ 4700 5800
NoConn ~ 4700 5700
NoConn ~ 4700 5600
NoConn ~ 4700 5500
NoConn ~ 4700 5400
NoConn ~ 4700 5300
NoConn ~ 4700 5200
NoConn ~ 4700 5100
NoConn ~ 4700 5000
NoConn ~ 4700 4900
NoConn ~ 4700 4800
NoConn ~ 4700 4700
NoConn ~ 4700 4400
Wire Wire Line
	4550 3550 4550 3450
$EndSCHEMATC
