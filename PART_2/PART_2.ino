
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
<<<<<<< Updated upstream
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5,5, PiN,
=======
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PiN,
>>>>>>> Stashed changes
                            NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB          + NEO_KHZ800  );



float accX = 0, accY = 0, accZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
float temp = 0;
float AvgTemp = 0;
<<<<<<< Updated upstream
=======
int ButtonPressedAtLeastOnce = 0;
bool case_activated = false;
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
 
=======

>>>>>>> Stashed changes
  matrix.setBrightness(20);
  matrix.setTextColor(colors[0]);
}

int z = matrix.height();
int y = 0;

int case_code = 0;

void loop()
{
<<<<<<< Updated upstream
  
=======
  matrix.setTextColor(colors[0]);
>>>>>>> Stashed changes
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



<<<<<<< Updated upstream
  if (M5.Btn.wasPressed() ) {
=======
  if (M5.Btn.wasPressed() || ButtonPressedAtLeastOnce == 1 ) {
    ButtonPressedAtLeastOnce = 1;
>>>>>>> Stashed changes

    switch (case_code) {

      case 0:
        for (;;) {

<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
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

<<<<<<< Updated upstream

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
      
=======
          if (abs(AvgAccX) < 0.4 || case_activated == true) {

            case_activated = true;

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

              break;

              //show the code needed to change  mode
            }


            else if ( AvgAccX < -0.4) {
              case_code = 4;
              break;
            }


          }
        }
        case_activated = false;
>>>>>>> Stashed changes
        break;







      case 1:

        for (;;) {

<<<<<<< Updated upstream
          CurrentTime = millis();
          
=======

          CurrentTime = millis();

>>>>>>> Stashed changes
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);

<<<<<<< Updated upstream
         
=======

>>>>>>> Stashed changes
          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

<<<<<<< Updated upstream
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
        
        
=======
          if (abs(AvgAccX) < 0.4 || case_activated == true) {
            case_activated = true;


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
              PreviousTime = millis();

            }

            if (AvgAccX > 0.4) { //tilting to the right
              case_code += 1;
              break;



            }


            else if ( AvgAccX < -0.4) {
              case_code -= 1;

              break;
            }
          }
        }
        case_activated = false;
        break;


>>>>>>> Stashed changes
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
<<<<<<< Updated upstream

          if (AvgAccZ < 0.7 && abs(AvgAccX) < 0.3) { // 0.3g = 27deg tilt angle
=======
          if (abs(AvgAccX) < 0.4 || case_activated == true) {
            case_activated = true;

>>>>>>> Stashed changes
            M5.dis.drawpix(0, 0, 0x0000ff); // blue
            M5.dis.drawpix(0, 1, 0x87cefa); // skyblue
            M5.dis.drawpix(0, 2, 0x008000); // green
            M5.dis.drawpix(0, 3, 0xffff00); // yellow
            M5.dis.drawpix(0, 4, 0xff0000); // red

            if (temp < 25) {
<<<<<<< Updated upstream
              for (int i = 2; i < 5; i++){
                for (int j = 1; j < 4; j++){
=======
              for (int i = 2; i < 5; i++) {
                for (int j = 1; j < 4; j++) {
>>>>>>> Stashed changes
                  M5.dis.drawpix(i, j, 0x0000ff);
                }
              }
            }

            else if (temp >= 25 && temp < 30) {
<<<<<<< Updated upstream
              for (int i = 2; i < 5; i++){
                for (int j = 1; j < 4; j++){
=======
              for (int i = 2; i < 5; i++) {
                for (int j = 1; j < 4; j++) {
>>>>>>> Stashed changes
                  M5.dis.drawpix(i, j, 0x87cefa);
                }
              }
            }

            else if (temp >= 30 && temp < 35) {
<<<<<<< Updated upstream
              for (int i = 2; i < 5; i++){
                for (int j = 1; j < 4; j++){
=======
              for (int i = 2; i < 5; i++) {
                for (int j = 1; j < 4; j++) {
>>>>>>> Stashed changes
                  M5.dis.drawpix(i, j, 0x008000);
                }
              }
            }

            else if (temp >= 35 && temp < 40) {
<<<<<<< Updated upstream
              for (int i = 2; i < 5; i++){
                for (int j = 1; j < 4; j++){
=======
              for (int i = 2; i < 5; i++) {
                for (int j = 1; j < 4; j++) {
>>>>>>> Stashed changes
                  M5.dis.drawpix(i, j, 0xffff00);
                }
              }
            }

            else {
<<<<<<< Updated upstream
              for (int i = 2; i < 5; i++){
                for (int j = 1; j < 4; j++){
=======
              for (int i = 2; i < 5; i++) {
                for (int j = 1; j < 4; j++) {
>>>>>>> Stashed changes
                  M5.dis.drawpix(i, j, 0xff0000);
                }
              }
            }
<<<<<<< Updated upstream
          }
          M5.clear();

          if (AvgAccX > 0.5) { //tilting to the right
=======
        
          //M5.clear();
          matrix.setTextColor(colors[0]);
          if (AvgAccX > 0.4) { //tilting to the right
>>>>>>> Stashed changes
            case_code += 1;
            break;


          }


<<<<<<< Updated upstream
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
        break;


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
        break;


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
=======
          else if (AvgAccX < -0.4) {
            case_code -= 1;
            break;
          }
        }
    }
    case_activated = false;
    break;


  case 3:
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

      if (abs(AvgAccX) < 0.4 || case_activated == true) {
        case_activated = true;
        if (CurrentTime - PreviousTime > 200) {
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
          PreviousTime = millis();
        }


        if (AvgAccX > 0.4) { //tilting to the right
          case_code += 1;
          break;


        }


        else if (AvgAccX < -0.4) {
          case_code -= 1;
          break;
        }
      }
    }
    case_activated = false;
    break;


  case 4:
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

      if (abs(AvgAccX) < 0.4 || case_activated == true) {
        case_activated = true;
        if (CurrentTime - PreviousTime > 200) {



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
          PreviousTime = millis();
        }

        if (AvgAccX > 0.4) { //tilting to the right
          case_code = 0;
          break;


        }


        else if (AvgAccX < -0.4) {
          case_code -= 1;
          break;
        }

      }
    }
    case_activated = false;
    break;

  default:
    break;


  }

}



M5.update();

}
>>>>>>> Stashed changes
