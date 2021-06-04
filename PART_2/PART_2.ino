
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



Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PiN,

                            NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB          + NEO_KHZ800  );



float accX = 0, accY = 0, accZ = 0;
float temp = 0;
float AvgTemp = 0;

int ButtonPressedAtLeastOnce = 0;
bool case_activated = false;


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

  M5.dis.drawpix(0, 0xf000000);

  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getTempData(&temp);



  int n_average = 15;
  // Averaging 15 different acceleration data to determine when the object tilts
  AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
  AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
  AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;






  if (M5.Btn.wasPressed() || ButtonPressedAtLeastOnce == 1 ) {
    ButtonPressedAtLeastOnce = 1;


    switch (case_code) {

      case 0:
        for (;;) {





          CurrentTime = millis();


          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);


          Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;


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

        break;







      case 1:

        for (;;) {


          CurrentTime = millis();



          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);


          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;


          if (abs(AvgAccX) < 0.4 || case_activated == true) {
            case_activated = true;


            if (CurrentTime - PreviousTime > 200) { // 0.3g = 27deg tilt angle

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



      case 2:

        for (;;) {

          CurrentTime = millis();


          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);


          Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;


          if (abs(AvgAccX) < 0.4 || case_activated == true) {
            case_activated = true;

            if (CurrentTime - PreviousTime > 200) {


              M5.dis.drawpix(0, 4, 0x0000ff); // blue
              M5.dis.drawpix(0, 3, 0xce87fa); // skyblue
              M5.dis.drawpix(0, 2, 0xff0000); // green
              M5.dis.drawpix(0, 1, 0xffff00); // yellow
              M5.dis.drawpix(0, 0, 0x00ff00); // red

              if (temp < 25) {

                for (int i = 2; i < 5; i++) {
                  for (int j = 1; j < 4; j++) {

                    M5.dis.drawpix(i, j, 0x0000ff);
                  }
                }
              }

              else if (temp >= 25 && temp < 30) {

                for (int i = 2; i < 5; i++) {
                  for (int j = 1; j < 4; j++) {

                    M5.dis.drawpix(i, j, 0xce87fa);
                  }
                }
              }

              else if (temp >= 30 && temp < 35) {

                for (int i = 2; i < 5; i++) {
                  for (int j = 1; j < 4; j++) {

                    M5.dis.drawpix(i, j, 0xff0000);
                  }
                }
              }

              else if (temp >= 35 && temp < 40) {

                for (int i = 2; i < 5; i++) {
                  for (int j = 1; j < 4; j++) {

                    M5.dis.drawpix(i, j, 0xffff00);
                  }
                }
              }

              else {

                for (int i = 2; i < 5; i++) {
                  for (int j = 1; j < 4; j++) {

                    M5.dis.drawpix(i, j, 0x00ff00);
                  }
                }
              }
              PreviousTime = millis();
            }



            M5.dis.drawpix(0, 0x000000);
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

      case 3:
        for (;;) {
          CurrentTime = millis();

          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);


          Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

          if (abs(AvgAccX) < 0.4 || case_activated == true) {
            case_activated = true;
            if (CurrentTime - PreviousTime > 200) {

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

          M5.IMU.getAccelData(&accX, &accY, &accZ);
          M5.IMU.getTempData(&temp);




          int n_average = 15;
          // Averaging 15 different acceleration data to determine when the object tilts
          AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
          AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
          AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

          if (abs(AvgAccX) < 0.4 || case_activated == true) {
            case_activated = true;
            if (CurrentTime - PreviousTime > 200) {




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
