#include <FastLED.h>

#include <M5Atom.h>

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



float accX = 0, accY = 0, accZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
float temp = 0;
float AvgTemp=0;
float AvgAccX = 0.0F;
float AvgAccY = 0.0F;
float AvgAccZ = 0.0F;

//define an array for displaying colors on the screen
const uint16_t colors[] = {
  Mode_Info.Color(255, 0, 0), Mode_Info.Color(0, 255, 0), Mode_Info.Color(0, 0, 255)
};


void setup()
{
  M5.begin(true, false, true);

  M5.IMU.Init();


  //initializing the matrix for displaying info
  Mode_Info.begin();
  Mode_Info.setTextWrap(false);
  Mode_Info.setBrightness(20);
  Mode_Info.setTextColor(colors[0]);
}

int z = Mode_Info.width();
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
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          Mode_Info.fillScreen(0);
          Mode_Info.setCursor(z, 0);
          Mode_Info.printf("Temperature : %.2f C", temp);
          if (--z < -36) {
            z = Mode_Info.width();
            if (++y >= 3) {
              y = 0;
            }
            Mode_Info.setTextColor(colors[y]);
          }
          Mode_Info.show();


          if (gyroX > 0.1) { //tilting to the right
            case_code += 1;
            break;
            
                    //show the code needed to change  mode
          }

          else if (gyroX < -0.1) {
            case_code = 4;
            break; 
          }
          break;



        }

        case 1:
        for (;;) {
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          Mode_Info.fillScreen(0);
          Mode_Info.setCursor(z, 0);
          Mode_Info.printf("Average Temperature is : %.2f C", AvgTemp);
          if (--z < -36) {
            z = Mode_Info.width();
            if (++y >= 3) {
              y = 0;
            }
            Mode_Info.setTextColor(colors[y]);
          }
          Mode_Info.show();


          if (gyroX > 0.1) { //tilting to the right
            case_code += 1;
            break;
            
                    //show the code needed to change  mode
          }

          else if (gyroX < -0.1) {
            case_code -= 1;
            break; 

          



        }
        case 2:
        for (;;) {
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          Mode_Info.fillScreen(0);
          Mode_Info.setCursor(z, 0);
          Mode_Info.printf("Temperature : %.2f C", temp);
          if (--z < -36) {
            z = Mode_Info.width();
            if (++y >= 3) {
              y = 0;
            }
            Mode_Info.setTextColor(colors[y]);
          }
          Mode_Info.show();


          if (gyroX > 0.1) { //tilting to the right
            case_code += 1;
            break;
            
                    //show the code needed to change  mode
          }

          else if (gyroX < -0.1) {
            case_code -= 1;
            break; 
          }
          break;



        }
        case 3:
        for (;;) {
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          Mode_Info.fillScreen(0);
          Mode_Info.setCursor(z, 0);
          Mode_Info.printf("Temperature : %.2f C", temp);
          if (--z < -36) {
            z = Mode_Info.width();
            if (++y >= 3) {
              y = 0;
            }
            Mode_Info.setTextColor(colors[y]);
          }
          Mode_Info.show();


          if (gyroX > 0.1) { //tilting to the right
            case_code += 1;
            break;
            
                    //show the code needed to change  mode
          }

          else if (gyroX < -0.1) {
            case_code -= 1;
            break; 
          }
          break;



        }
        case 4:
        for (;;) {
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          Mode_Info.fillScreen(0);
          Mode_Info.setCursor(z, 0);
          Mode_Info.printf("Temperature : %.2f C", temp);
          if (--z < -36) {
            z = Mode_Info.width();
            if (++y >= 3) {
              y = 0;
            }
            Mode_Info.setTextColor(colors[y]);
          }
          Mode_Info.show();


          if (gyroX > 0.1) { //tilting to the right
            case_code = 0;
            break;
            
                    //show the code needed to change  mode
          }

          else if (gyroX < -0.1) {
            case_code -= 1;
            break; 
          }
          break;



        }

    }


  }





}
