#include <M5Atom.h>

#include <FastLED.h>


void setup() {
  // put your setup code here, to run once:
  // Initialising the device
  M5.begin(true, false, true);
  delay(50);
}

uint8_t case_code = 0; // Denoting the current case of the display

void loop() {
  // put your main code here, to run repeatedly:
  if (M5.Btn.wasPressed()) // Detecting if the button is pressed
  {

    switch (case_code) 
    {
      case 0:
          for (;M5.Btn.wasPressed();)
          {
            M5.dis.fillpix(0xff0000); // Strobe with red colour
            delay(200);
            M5.dis.clear();
            delay(200);
          }
          break;

       case 1:
          for (;M5.Btn.wasPressed();)
          {
            M5.dis.fillpix(0xffffff); // Strobe with white colour
            delay(200);
            M5.dis.clear();
            delay(200);
          }
          break;

       case 2:
          for (;M5.Btn.wasPressed();)
          {
            // Reserved for auto red. How to incorporate accelerometer?  
          }
          break;

       case 3:
          for (;M5.Btn.wasPressed();)
          {
            // Same for auto white.
          }
          break;

       default:
          break;

      case_code ++;

      if (case_code >= 4)
      {
        case_code = 0;
      }
    }
  }
}
