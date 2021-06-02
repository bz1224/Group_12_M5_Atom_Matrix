<<<<<<< HEAD



#include <FastLED.h>

#include <M5Atom.h>

=======
#include <M5Atom.h>
#include <FastLED.h>

#include <TimeLib.h>
>>>>>>> 568403475bd3d75085f936946b087df8072ec5ac
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PiN 27

//Declare matrix needed to display information
//First two parameters give width and height of the matrix
//Fourth parameter gives the matrix layout
<<<<<<< HEAD
Adafruit_NeoMatrix Mode_Info = Adafruit_NeoMatrix(5, 5, PiN,
                               NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                               NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                               NEO_GRB          + NEO_KHZ800 );
=======
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 3, PiN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB          + NEO_KHZ800  );
>>>>>>> 568403475bd3d75085f936946b087df8072ec5ac



float accX = 0, accY = 0, accZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
float temp = 0;
<<<<<<< HEAD
float AvgTemp=0;
=======
float AvgTemp = 0;
>>>>>>> 568403475bd3d75085f936946b087df8072ec5ac

float AvgAccX = 0.0F;
float AvgAccY = 0.0F;
float AvgAccZ = 0.0F;
<<<<<<< HEAD

=======
unsigned long CurrentTime;
unsigned long PreviousTime = 0;
>>>>>>> 568403475bd3d75085f936946b087df8072ec5ac


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

int z = matrix.width();
int y = 0;

int case_code = 0;

void loop()
{
  
  /*M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getTempData(&temp);

  Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
  Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

  int n_average = 15;
  // Averaging 15 different acceleration data to determine when the object tilts
  AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
  AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
  AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;*/



  if (M5.Btn.wasPressed() ) {

    switch (case_code) {

      case 0:
        for (;;) {

          CurrentTime = millis();

          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
<<<<<<< HEAD
          Mode_Info.fillScreen(0);
          Mode_Info.setCursor(z, 0);
          //Mode_Info.printf("Temperature : %.2f C", temp);
          Mode_Info.print(F("TEMP"));
          if (--z < -36) {
            z = Mode_Info.width();
            if (++y >= 3) {
              y = 0;
=======
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
>>>>>>> 568403475bd3d75085f936946b087df8072ec5ac
            }
            matrix.show();

          }



          if (AvgAccZ > 0.7 && AvgAccX > 0.3) { //tilting to the right
            case_code += 1;
            delay(2000);
            break;

            //show the code needed to change  mode
          }


          else if (AvgAccZ > 0.7 && AvgAccX < -0.3) {
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
            if (--z < -76) {
              z = matrix.width();
              if (++y >= 3) {
                y = 0;
              }
              matrix.setTextColor(colors[y]);
            }
            matrix.show();

          }

          if (AvgAccZ > 0.7 && AvgAccX > 0.3) { //tilting to the right
            case_code += 1;
            break;


          }


          else if (AvgAccZ > 0.7 && AvgAccX < -0.3) {
            case_code -= 1;
            break;
          }

        }
        break;
        
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
            case_code += 1;
            break;


          }


          else if (AvgAccX < -0.5) {
            case_code -= 1;
            break;
          }

        }


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



<<<<<<< HEAD

M5.update();
  }
}
  
 

 
=======
  M5.update();

}
>>>>>>> 568403475bd3d75085f936946b087df8072ec5ac
