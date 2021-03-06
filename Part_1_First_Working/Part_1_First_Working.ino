#include <M5Atom.h>

#include <FastLED.h>

#include <TimeLib.h>

#define interval1 400
#define interval2 200

uint8_t DisBuff[2 + 5 * 5 * 3];

void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
  DisBuff[0] = 0x05;
  DisBuff[1] = 0x05;
  for (int i = 0; i < 25; i++)
  {
    DisBuff[2 + i * 3 + 0] = Rdata;
    DisBuff[2 + i * 3 + 1] = Gdata;
    DisBuff[2 + i * 3 + 2] = Bdata;
  }
}


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

}

int x = 0;
unsigned long CurrentTime;
unsigned long PreviousTime;

// Detecting constantly for pressed button, change the case accordingly.
void loop() {

  M5.update();
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
        CurrentTime = millis();
        if (CurrentTime - PreviousTime >= interval1) {
          setBuff(0xff, 0x00, 0x00);
          M5.dis.displaybuff(DisBuff);; // Strobe with red colour
          PreviousTime = millis();
        }
        if (CurrentTime - PreviousTime >= interval2) {
          M5.dis.clear();
        }


        //code needed for scrolling text


        if (main_btn.pressed) {
          main_btn.pressed = false;
          break;
        }
      }
      break;

    case 2:


      for (;;)
      {
        CurrentTime = millis();
        if (CurrentTime - PreviousTime >= interval1) {
          M5.dis.fillpix(0xffffff); // Strobe with white colour
          PreviousTime = millis();
        }
        if (CurrentTime - PreviousTime >= interval2) {
          M5.dis.clear();
        }


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
      { x = 0;
        CurrentTime = millis();
        if (CurrentTime - PreviousTime >= interval1) {
          setBuff(0xff, 0x00, 0x00);
          M5.dis.displaybuff(DisBuff); // Strobe with red colour
          PreviousTime = millis();
        }
        if (CurrentTime - PreviousTime >= interval2) {
          M5.dis.clear();
        }

        M5.IMU.getAccelData(&accX, &accY, &accZ);
        // Taking the 3D acceleration as a vector and calculating the square of its magnitude
        //Previous value = 6.25
        if (accX * accX + accZ * accZ > 1) {
          for (;;) {
            setBuff(0xff, 0x00, 0x00);
            M5.dis.displaybuff(DisBuff); // Strobe with red colour
            M5.IMU.getAccelData(&accX, &accY, &accZ);
            if (main_btn.pressed) {
              main_btn.pressed = false;
              x = 1;

              break;
            }


            if (accX * accX + accZ * accZ < 1) {
              break;
            }

          }


        }
        if (x == 1) {
          break;
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
        x = 0;
        CurrentTime = millis();
        if (CurrentTime - PreviousTime >= interval1) {
          M5.dis.fillpix(0xffffff); // Strobe with white colour
          PreviousTime = millis();
        }
        if (CurrentTime - PreviousTime >= interval2) {
          M5.dis.clear();
        }

        M5.IMU.getAccelData(&accX, &accY, &accZ);
        // Taking the 3D acceleration as a vector and calculating the square of its magnitude
        //Previous value = 6.25
        if (accX * accX + accZ * accZ > 1) {
          for (;;) {
            M5.dis.fillpix(0xffffff); // Strobe with white colour
            M5.IMU.getAccelData(&accX, &accY, &accZ);
            if (main_btn.pressed) {
              main_btn.pressed = false;
              x = 1;

              break;
            }


            if (accX * accX + accZ * accZ < 1) {
              break;
            }

          }


        }
        if (x == 1) {
          break;
        }

        if (main_btn.pressed) {
          main_btn.pressed = false;
          break;
        }
      }
      break;

    default:
      break;


  }

}
