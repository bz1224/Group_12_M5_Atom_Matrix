+#include <M5Atom.h>

#include <FastLED.h>

#include <TimeLib.h>


//Libraries needed for scrolling text
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PiN 5

//Declare matrix needed to display information
//First two parameters give width and height of the matrix
//Fourth parameter gives the matrix layout
Adafruit_NeoMatrix Mode_Info = Adafruit_NeoMatrix(5, 5, PiN,
                               NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                               NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                               NEO_KHZ800           + NEO_GRB );

//define an array for displaying colors on the screen
const uint16_t colors[] = {
  Mode_Info.Color(255, 0, 0), Mode_Info.Color(0, 255, 0), Mode_Info.Color(0, 0, 255)
};

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

  //initializing the matrix for displaying info
  Mode_Info.begin();
  Mode_Info.setTextWrap(false);
  Mode_Info.setBrightness(20);
  Mode_Info.setTextColor(colors[0]);
}

int z = Mode_Info.width();
int y = 0;
unsigned long CurrentTime;

// Detecting constantly for pressed button, change the case accordingly.
void loop() {

  CurrentTime = millis();

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

      M5.dis.fillpix(0xff0000); // Strobe with red colour
      for (;;)
      {


        if (millis() >= CurrentTime + 200) {
          M5.dis.clear();
          CurrentTime = millis();
        }

        if (millis() >= CurrentTime + 100 && millis() < CurrentTime + 200) {
          M5.dis.fillpix(0xff0000);
        }


        //code needed for scrolling text
        Mode_Info.fillScreen(0);
        Mode_Info.setCursor(z, 0);
        Mode_Info.print(F("MANUAL REAR STROBE"));
        if (--z < -36) {
          z = Mode_Info.width();
          if (++y >= 3) {
            y = 0;
          }
          Mode_Info.setTextColor(colors[y]);
        }
        Mode_Info.show();



        if (main_btn.pressed) {
          main_btn.pressed = false;
          break;
        }
      }
      break;

    case 2:

      M5.dis.fillpix(0xffffff); // Strobe with white colour
      for (;;)
      {
        if (millis() >= CurrentTime + 200) {
          M5.dis.clear();
          CurrentTime = millis();
        }

        if (millis() >= CurrentTime + 100 && millis() < CurrentTime + 200) {
          M5.dis.fillpix(0xff0000);
        }

        Mode_Info.fillScreen(0);
        Mode_Info.setCursor(z, 0);
        Mode_Info.print(F("MANUAL FRONT STROBE"));
        if (--z < -36) {
          z = Mode_Info.width();
          if (++y >= 3) {
            y = 0;
          }
          Mode_Info.setTextColor(colors[y]);
        }
        Mode_Info.show();

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

      M5.dis.fillpix(0xff0000); // Strobe with red colour
      for (;;)
      {
        Mode_Info.fillScreen(0);
        Mode_Info.setCursor(z, 0);
        Mode_Info.print(F("AUTOMATIC REAR MODE"));
        if (--z < -36) {
          z = Mode_Info.width();
          if (++y >= 3) {
            y = 0;
          }
          Mode_Info.setTextColor(colors[y]);
        }
        Mode_Info.show();

        M5.IMU.getAccelData(&accX, &accY, &accZ);
        // Taking the 3D acceleration as a vector and calculating the square of its magnitude
        if (accX * accX + accY * accY + accZ * accZ > 6.25) {
          continue;
        }
        else {
          CurrentTime = millis();
          M5.dis.clear();
          for (;;) {
            if (millis() >= CurrentTime + 200) {
              M5.dis.fillpix(0xff0000);
              CurrentTime = millis();
              break;
            }
          }


        }
        if (main_btn.pressed) {
          main_btn.pressed = false;
          break;
        }
      }
      break;

    case 4:
      M5.dis.fillpix(0xffffff); // Strobe with white colour
      for (;;)
      {
        Mode_Info.fillScreen(0);
        Mode_Info.setCursor(z, 0);
        Mode_Info.print(F("AUTOMATIC FRONT MODE"));
        if (--z < -36) {
          z = Mode_Info.width();
          if (++y >= 3) {
            y = 0;
          }
          Mode_Info.setTextColor(colors[y]);
        }
        Mode_Info.show();

        M5.IMU.getAccelData(&accX, &accY, &accZ);
        // Taking the 3D acceleration as a vector and calculating the square of its magnitude
        if (accX * accX + accY * accY + accZ * accZ > 6.25) {
          continue;
        }
        else {
          CurrentTime = millis();
          M5.dis.clear();
          for (;;) {
            if (millis() >= CurrentTime + 200) {
              M5.dis.fillpix(0xffffff);
              CurrentTime = millis();
              break;
            }
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
}
