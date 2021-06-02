
#include <M5Atom.h>
#include <FastLED.h>
#include <TimeLib.h>
#include <Adafruit_GFX.h>
#include <Fonts/TomThumb.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PiN 27

//Declare matrix needed to display information
//First two parameters give width and height of the matrix
//Fourth parameter gives the matrix layout
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5,5, PiN,
                            NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB          + NEO_KHZ800  );



float accX = 0, accY = 0, accZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
float temp = 0;
float AvgTemp = 0;

float AvgAccX = 0.0F;
float AvgAccY = 0.0F;
float AvgAccZ = 0.0F;
unsigned long CurrentTime;
unsigned long PreviousTime = 0;


//define an array for displaying colors on the screen
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};


void setup()
{
  M5.begin(true, false, true);

  M5.IMU.Init();


  //initializing the matrix for displaying info
  matrix.begin();
  matrix.setTextWrap(false);
 
  matrix.setBrightness(20);
  matrix.setTextColor(colors[0]);
}

int z = matrix.height();
int y = 0;

int case_code = 0;

void loop()
{
  
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getTempData(&temp);

  Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
  Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

  int n_average = 15;
  // Averaging 15 different acceleration data to determine when the object tilts
  AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
  AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
  AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;



  if (M5.Btn.wasPressed() ) {

    switch (case_code) {

      case 0:
        for (;;) {

          CurrentTime = millis();

          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);

          Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
          Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;


          if (CurrentTime - PreviousTime > 200) {
            PreviousTime = millis();
            matrix.fillScreen(0);
            matrix.setCursor(z, 0);
            matrix.printf("TEMPERATURE : %.2f ", temp);
            if (--z < -106) {
              z = matrix.width();
              if (++y >= 3) {
                y = 0;
              }
              matrix.setTextColor(colors[y]);
            }
            matrix.show();

          }



          if (AvgAccX > 0.4) { //tilting to the right
            case_code += 1;
            delay(2000);
            break;

            //show the code needed to change  mode
          }


          else if ( AvgAccX < -0.4) {
            case_code = 4;
            delay(2000);
            break;
          }


        }
      
break;







      case 1:

        for (;;) {

          CurrentTime = millis();
          
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);

         
          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

          if (CurrentTime - PreviousTime > 200) { // 0.3g = 27deg tilt angle
            M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
            matrix.fillScreen(0);
            matrix.setCursor(z, 0);
            matrix.printf("AVERAGE TEMPERATURE IS : % .2f C", AvgTemp);
            if (--z < -106) {
              z = matrix.width();
              if (++y >= 3) {
                y = 0;
              }
              matrix.setTextColor(colors[y]);
            }
            matrix.show();
            PreviousTime=millis();

          }

          if (AvgAccX > 0.3) { //tilting to the right
            case_code += 1;
            break;
            delay(1000);


          }


          else if ( AvgAccX < -0.3) {
            case_code -= 1;
            delay(1000);
            break;
          }
          break;

        }
        
        
      case 2:

        for (;;) {
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);

          Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
          Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

          if (AvgAccZ < 0.7 && abs(AvgAccX) < 0.3) { // 0.3g = 27deg tilt angle
            M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
            matrix.fillScreen(0);
            matrix.setCursor(z, 0);
            matrix.printf("Mode 3");
            if (--z < -106) {
              z = matrix.width();
              if (++y >= 3) {
                y = 0;
              }
              matrix.setTextColor(colors[y]);
            }
            matrix.show();
            PreviousTime=millis();
          }

          if (AvgAccX > 0.5) { //tilting to the right
            case_code += 1;
            break;


          }


          else if (AvgAccX < -0.5) {
            case_code -= 1;
            break;
          }

        }
        break;


      case 3:
        for (;;) {
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);

          Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
          Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

          if (AvgAccZ < 0.7 && abs(AvgAccX) < 0.3) { // 0.3g = 27deg tilt angle
            M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
            matrix.fillScreen(0);
            matrix.setCursor(z, 0);
            matrix.printf("Mode 4");
            if (--z < -106) {
              z = matrix.width();
              if (++y >= 3) {
                y = 0;
              }
              matrix.setTextColor(colors[y]);
            }
            matrix.show();
            PreviousTime=millis();
          }

          if (AvgAccX > 0.5) { //tilting to the right
            case_code += 1;
            break;


          }


          else if (AvgAccX < -0.5) {
            case_code -= 1;
            break;
          }

        }


      case 4:
        for (;;) {
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);

          Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
          Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

          if (AvgAccZ < 0.7 && abs(AvgAccX) < 0.3) { // 0.3g = 27deg tilt angle
            M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
            matrix.fillScreen(0);
            matrix.setCursor(z, 0);
            matrix.printf("Mode 5");
            if (--z < -76) {
              z = matrix.width();
              if (++y >= 3) {
                y = 0;
              }
              matrix.setTextColor(colors[y]);
            }
            matrix.show();
            delay (100);
          }

          if (AvgAccX > 0.5) { //tilting to the right
            case_code = 0;
            break;


          }


          else if (AvgAccX < -0.5) {
            case_code -= 1;
            break;
          }

        }


    }


  }



  M5.update();

}

/*
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/TomThumb.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 27

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setFont(&TomThumb);
  matrix.setBrightness(20);
  matrix.setTextColor(colors[0]);
}

int x   = matrix.height();
int pass = 0;

void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, matrix.height());
  matrix.print(F("Hello World"));
  if(--x < -60) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(200);
}
*/
