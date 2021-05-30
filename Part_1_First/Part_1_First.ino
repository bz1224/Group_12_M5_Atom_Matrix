#include <M5Atom.h>

#include <FastLED.h>

#include <TimeLib.h>


//Libraries needed for scrolling text
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 5

//Declare matrix needed to display information
//First two parameters give width and height of the matrix
//Fourth parameter gives the matrix layout
Adafruit_NeoMatrix Mode_Info = Adafruit_NeoMatrix(5, 5, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
 NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_KHZ800           + NEO_GRB );

//define an array for displaying colors on the screen
const uint16_t colors[] = {
  Mode_Info.Color(255, 0, 0), Mode_Info.Color(0, 255, 0), Mode_Info.Color(0, 0, 255) };

void setup() {
  // put your setup code here, to run once:
  // Initialising the device
  M5.begin(true, false, true);
  //initializing the matrix for displaying info
  Mode_Info.begin();
  Mode_Info.setTextWrap(false);
  Mode_Info.setBrightness(20);
  Mode_Info.setTextColor(colors[0]);
  delay(50);
}

uint8_t case_code = 0; // Denoting the current case of the display

int z    = Mode_Info.width();
int y = 0;
unsigned long CurrentTime;


void loop() {
  // put your main code here, to run repeatedly:
  CurrentTime = millis();
  if (M5.Btn.wasPressed()) // Detecting if the button is pressed
  {

    switch (case_code) 
    {
      case 0:
          M5.dis.fillpix(0xff0000); // Strobe with red colour
          for (;M5.Btn.wasPressed();)
          {           
            if (millis()>=CurrentTime+200){
              M5.dis.clear();  
              CurrentTime=millis();            
            }
            
            if (millis()>=CurrentTime+100 && millis()<CurrentTime+200){
               M5.dis.fillpix(0xff0000);                            
            }
            

            Mode_Info.fillScreen(0);
            Mode_Info.setCursor(z, 0);
             Mode_Info.print(F("MANUAL REAR STROBE"));
             if(--z < -36) {
              z = Mode_Info.width();
              if(++y >= 3){ 
              y = 0;
              }
             Mode_Info.setTextColor(colors[y]);
             }
             Mode_Info.show();
           
             
          }
          break;

       case 1:

          M5.dis.fillpix(0xffffff); // Strobe with white colour
          for (;M5.Btn.wasPressed();)
          {
            if (millis()>=CurrentTime+200){
              M5.dis.clear();  
              CurrentTime=millis();            
            }

             if (millis()>=CurrentTime+100 && millis()<CurrentTime+200){
               M5.dis.fillpix(0xff0000);                            
            }

             Mode_Info.fillScreen(0);
            Mode_Info.setCursor(z, 0);
             Mode_Info.print(F("MANUAL FRONT STROBE"));
             if(--z < -36) {
              z = Mode_Info.width();
              if(++y >= 3){ 
              y = 0;
              }
             Mode_Info.setTextColor(colors[y]);
             }
             Mode_Info.show();
            
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
