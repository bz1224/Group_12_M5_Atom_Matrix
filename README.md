# Group_12_M5_Atom_Matrix
 This is the collection of codes for M5_Atom_Matrix assignment from Group 12

Part 1 First: Bicycle Light Simulation

Code execution:

Open Part_1_First_Working.ino in Part_1_First_Working folder in Arduino IDE. Set the development board to M5Stack Atom, with reference to instructions at https://docs.m5stack.com/en/arduino/arduino_development. Import M5Atom, FastLED and Time libraries from Sketch -> Load Library -> Manage Libraries if these libraries are not locally available. Set the baud rate to 115200 at Tools -> Upload speed. Press the -> button on the top right hand corner of the IDE to update the code to M5Stack Atom Matrix when this device is connected to the computer via a USB-C to USB cable. 

Necessary libraries:
M5Atom, FastLED, TimeLib.

Modes available: 

1. OFF Mode: where all LEDs are off. 
2. Manual Rear Strobe Mode: all LEDs become red and strobe at the pace of 400ms lit/200ms off.
3. Manual Front Strobe Mode: all LEDs become white and strobe at the pace of 400ms lit/200ms off. 
4. Automatic Rear Mode: LEDs are solid and red during a braking event. Return to strobe with the same intervals when riding.
5. Automatic Front Mode: LEDs are solid and white during a braking event. Return to strobe with the same intervales when riding. 

Orientation specification:

The USB-C port on M5Stack Atom Matrix should face the ground to properly perform the functions of this device. 

Switching between modes:

The 5 modes above transit from one to the other in a numerical order and in one direction only. Each time the button of the M5Stack Atom Matrix is pressed, the device changes its working mode. At Mode 5, when the button is pressed, the device will change to Mode 1. 

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Part 1 Second: Temperature Measurement Complex

Code execution:

Open PART_1_Second.ino in PART_1_Second folder in Arduino IDE. The rest of necessary steps are the same as in Part 1 First.

Necessary libraries:
M5Atom, FastLED, TimeLib.

Modes available:

1. Temperature Mode: Displaying current temperature measured by MPU6886 embedded in M5Stack Atom Matrix (in C or in F).
2. Average Temperature Mode: Displaying average temperature measured over a period of time.
3. Temperature Colour Scale Mode: LEDs on the leftmost column show a scale of temperatures, categorised with boundaries of 25, 30, 35, 40. LEDs on the right show the range currently the temperature falls into.
4. Temperature Plot Mode: Green LEDs shows the live fluctuation of temperatures
5. Unit Switching Mode: The temperature displayed in Modes 1 and 2 can be converted to the other unit (C to F or F to C) when this mode is activated. 

Orientation specification:

The USB-C port on M5Stack Atom Matrix should face the ground to properly perform the functions of this device. 

Operating instructions:

1. When the power is already available, pressing on the M5 Atom Matrix will print “ i ” on the screen. This letter “i” refers to the first mode.
2. Tilting the device to the left and right will move you through the different 5 modes and so it print on the screen after each tilt a letter representing the mode such as “ii and iii and iv and v”.
3. Pressing on the button again when a certain letter appears on the screen will take the user to the screen that display the functions of the current mode.
4. If the user presses the button when letter i is appearing on the screen then the device will show the active temperature + the units on the screen.
5. If the user presses the button when letter ii is appearing on the screen then the device will show the average temperature of last 24 hours  + the units
6. If the user presses the button when letter iii is appearing on the screen then the device will show the color scale of temperature range + current temperature as color
7. If the user presses on the button when letter iv is appearing on the screen then the device will show graph of temperature over last 12 seconds, which will be initially represented as a straight line through a certain row that gets updated every 12 seconds based on how temperature changed in last 12 seconds.
8. If the user presses on the button when letter v is appearing on the screen then the device will change the units of temperature, so if the unit was in Celsius pressing on v will change the unit to Fahrenheit and if the temperature was in Fahrenheit then pressing on v will change the unit to Celsius.
9. To exit any active display mode the user will have to turn the device face-down and the device returns to background reading.
10.	Pressing on the button when the device is in background reading will display again the letter for each mode.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Part 2: Fidget Spinner Frequency and Strength Determination

Hardware preparation: 

M5Stack Atom Matrix is mounted on a predesigned PCB, housed in a spinner shaped casing. 

Code execution:

Open Fidget_Spinner_Sensoring_Functions.ino in Fidget_Spinner_Sensoring_Functions in Arduino IDE. The rest of necessary steps are the same as in Part 1 First.

Necessary Libraries:
M5Atom, FastLED, WiFi, WiFiClient, WiFiAP.

Functionalities:

Monitor the number of fidget events per hour (fidgeting frequency) over the latest 24 hours and display these data on a webpage set by M5Stack Atom Matrix, and indicate the happening of a strong fidget by displaying red LEDs on the screen of M5Stack Atom Matrix. 

Orientation specification:

The fidget spinner, as well as the M5Stack Atom Matrix device, should be oriented roughly parallel to the ground. 

Operating instructions:

1. After the code is executed, connected handphone or computer WiFi to "Group_12_Fidget_Spinner" with the password "abcdefgh" (quotation marks are not part of the password).
2. While connected to this WiFi, open up any browser application and key in an address: 192.168.4.1. 
3. On this webpage, press the only hyperlink available to keep track of the changing number of fidgets within one hour. 
4. Every hour, the latest number is going to be re-zeroed and previous data will be preserved in lines above. A maximum of 24 data can be preserved. 
