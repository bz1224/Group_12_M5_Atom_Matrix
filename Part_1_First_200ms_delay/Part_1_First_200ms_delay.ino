#include <M5Atom.h>

#include <FastLED.h>

// Inplementing Interrupt Service Routine for detecting button pressed during strobe
// Reference is from https://lastminuteengineers.com/handling-esp32-gpio-interrupts-tutorial/

// Creating a struct for the button
struct screen_button {
  const uint8_t PIN; // Denoting the PIN port of the button on PIN map
  uint32_t case_code; // Denoting current state of display
  bool pressed; // Denoting the state of being pressed or not
};

screen_button main_btn = {39, 0, false}; // In M5Stack Atom Matrix documentation, the PIN port of the button is G39

// Invoking the Interrupt Service Routine on the internal RAM of the device
void IRAM_ATTR isr() {
  main_btn.case_code += 1;
  main_btn.pressed = true;
  if (main_btn.case_code > 4) {
    main_btn.case_code = 0;
  }
}

// Initialising the device
void setup() {
  M5.begin(true, false, true);
  M5.IMU.Init();
  pinMode(main_btn.PIN, INPUT_PULLUP);
  attachInterrupt(main_btn.PIN, isr, FALLING); // Attaching the ISR to the button
  delay(50);
}

// Detecting constantly for pressed button, change the case accordingly. 
void loop() {
  float accX, accY, accZ;
  
  switch (main_btn.case_code) 
  {

    case 0:
        for (;;) 
        {
          M5.dis.fillpix(0x000000); // Keeping the LEDs black
          if (main_btn.pressed) {
             main_btn.pressed = false;
             break;
          }
        }
        
    case 1:
        for (;;)
        {
          M5.dis.fillpix(0xff0000); // Strobe with red colour
          delay(200);
          M5.dis.clear();
          delay(200);
          if (main_btn.pressed) {
            main_btn.pressed = false;
            break;
          }
        }
        break;

     case 2:
        for (;;)
        {
          M5.dis.fillpix(0xffffff); // Strobe with white colour
          delay(200);
          M5.dis.clear();
          delay(200);
          if (main_btn.pressed) {
            main_btn.pressed = false;
            break;
          }
        }
        break;
        
// For determining a braking event, https://www.sae.org/publications/technical-papers/content/2020-01-0876/
// suggests that deceleration of a bicycle is approximately between 0.25 to 0.36 g, 
// meaning that it will be more than 2.5 m/s^2. 2.5^2 = 6.25. 

     case 3:
        for (;;)
        {
          M5.dis.fillpix(0xff0000); // Strobe with red colour
          delay(200);
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          // Taking the 3D acceleration as a vector and calculating the square of its magnitude
          if (accX * accX + accY * accY + accZ * accZ > 6.25) {
            continue;
          }
          else {
            M5.dis.clear();
            delay(200);
          }
          if (main_btn.pressed) {
            main_btn.pressed = false;
            break;
          }  
        }
        break;
        
     case 4:
        for (;;)
        {
          M5.dis.fillpix(0xffffff); // Strobe with white colour
          delay(200);
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          // Taking the 3D acceleration as a vector and calculating the square of its magnitude
          if (accX * accX + accY * accY + accZ * accZ > 6.25) {
            continue;
          }
          else {
            M5.dis.clear();
            delay(200);
          }
          if (main_btn.pressed) {
            main_btn.pressed = false;
            break;
          }
        }
        break;
        
      default: 
        break;

  M5.update();
  }
}
