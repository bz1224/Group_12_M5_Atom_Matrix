
#include <Adafruit_GFX.h>


#include <gfxfont.h>

#include <Adafruit_NeoMatrix.h>


#include <Adafruit_NeoPixel.h>



#include <M5Atom.h>
#include <FastLED.h>
#include <TimeLib.h>

#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PiN 27
#define OneHour 3600000
//Declare matrix needed to display information
//First two parameters give width and height of the matrix
//Fourth parameter gives the matrix layout



Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PiN,

                            NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB          + NEO_KHZ800  );



float accX = 0, accY = 0, accZ = 0;
float temp = 0;
float AvgTemp = 0;
float TempSum = 0;
float TempOverLast24Hours [24] = {0};
int i = 0, cnt = 0, j = 0, k = 0;

int ButtonPressedAtLeastOnce = 0;
bool case_activated = false;


float AvgAccX = 0.0F;
float AvgAccY = 0.0F;
float AvgAccZ = 0.0F;
unsigned long CurrentTime;
unsigned long PreviousTime = 0;
unsigned long TimeSinceLastTempReading = millis();


//define an array for displaying colors on the screen
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};



unsigned char TempGraph[77] =
{
  /* width  005 */ 0x05,
  /* height 005 */ 0x05,
  /* Line   000 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   001 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   002 */ 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, //
  /* Line   003 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   004 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
};


unsigned char Case_i[77] =
{
  /* width  005 */ 0x05,
  /* height 005 */ 0x05,
  /* Line   000 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   001 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   002 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   003 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   004 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
};
unsigned char Case_ii[77] =
{
  /* width  005 */ 0x05,
  /* height 005 */ 0x05,
  /* Line   000 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, //
  /* Line   001 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   002 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, //
  /* Line   003 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, //
  /* Line   004 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, //
};

unsigned char Case_iii[77] =
{
  /* width  005 */ 0x05,
  /* height 005 */ 0x05,
  /* Line   000 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, //
  /* Line   001 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   002 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, //
  /* Line   003 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, //
  /* Line   004 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, //
};


unsigned char Case_iv[77] =
{
  /* width  005 */ 0x05,
  /* height 005 */ 0x05,
  /* Line   000 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   001 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, //
  /* Line   002 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, //
  /* Line   003 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
  /* Line   004 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, //
};
unsigned char Case_v[77] =
{
  /* width  005 */ 0x05,
  /* height 005 */ 0x05,
  /* Line   000 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, //
  /* Line   001 */ 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, //
  /* Line   002 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, //
  /* Line   003 */ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, //
  /* Line   004 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //
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
  M5.IMU.getTempData(&temp);
  i = 0;
  for (i = 0; i < 24; i++) {
    TempOverLast24Hours[i] = temp;
  }
}

int z = matrix.height() - 1;
int y = 0;

int case_code = 0;

void loop()
{
  i = 0;
  M5.dis.drawpix(0, 0xf000000);
  case_activated = false;

  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getTempData(&temp);
  //Averaging the temperature over last 24 hours
  if (millis() >= TimeSinceLastTempReading + OneHour) {
    if (i == 23) {
      for ( cnt = 0; cnt = 22; cnt++) {
        //remove the most outdated temp value and add the newest one
        TempOverLast24Hours[cnt] = TempOverLast24Hours[cnt + 1];
      }
      TempOverLast24Hours[cnt + 1] = temp;
    }


    else if (i < 23) {

      TempOverLast24Hours[i + 1] = temp;
      i += 1;

    }
    TimeSinceLastTempReading = millis();
  }



  int n_average = 15;
  // Averaging 15 different acceleration data to determine when the object tilts
  AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
  AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
  AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;


  CurrentTime = millis();
  if (CurrentTime - PreviousTime >= 12000) {
    k = 0;
    for (k = 0; k < 71; k++) {
      if (k % 15 != 0) {
        TempGraph[k + 3] = TempGraph[k + 6];
      }
      else {
        TempGraph[k] = 0x00;
        TempGraph [75] = 0x00;
      }
    }

    if (temp >= 20 && temp < 30) {

      TempGraph [75] = 0xff;

    }


    else if (temp >= 30 && temp < 35) {

      TempGraph [60] = 0xff;

    }

    else if (temp >= 35 && temp < 40) {
      TempGraph[45] = 0xff;
    }
    else if (temp >= 40 && temp < 45) {
      TempGraph [30] = 0xff;
    }
    else if (temp >= 45 && temp < 50) {
      TempGraph[15] = 0xff;
    }
    PreviousTime = millis();
  }

  if (M5.Btn.wasPressed() || ButtonPressedAtLeastOnce == 1 ) {
    ButtonPressedAtLeastOnce = 1;


    switch (case_code) {

      case 0:

        if (abs(AvgAccX) < 0.4 || case_activated == true) {
          case_activated = true;



          M5.dis.displaybuff(Case_i);

          if (M5.Btn.wasPressed()) {
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


              if (abs(AvgAccZ) > 0.4) //return back to main menu
              {
                break;
              }

            }
          }
          if (AvgAccX > 0.4) { //tilting to the right
            case_code += 1;

            break;

          }



          else if ( AvgAccX < -0.4) { //tilting to the left
            case_code = 4;

            break;
          }

        }



      case 1:

        if (abs(AvgAccX) < 0.4 || case_activated == true) {
          case_activated = true;



          M5.dis.displaybuff(Case_ii);

          if (M5.Btn.wasPressed()) {
            for (;;) {
              TempSum = 0;
              AvgTemp = 0;

              CurrentTime = millis();




              M5.IMU.getAccelData(&accX, &accY, &accZ);
              M5.IMU.getTempData(&temp);

              //Averaging the temperature over last 24 hours
              if (millis() >= TimeSinceLastTempReading + OneHour) {
                if (i == 23) {
                  for ( cnt = 0; cnt = 22; cnt++) {
                    //remove the most outdated temp value and add the newest one
                    TempOverLast24Hours[cnt] = TempOverLast24Hours[cnt + 1];
                  }
                  TempOverLast24Hours[cnt + 1] = temp;
                }





                else if (i < 23) {

                  TempOverLast24Hours[i + 1] = temp;
                  i += 1;

                }
                TimeSinceLastTempReading = millis();
              }


              //Sum values of temp over last 24 hours
              for (int j = 0; j < 23; j++) {
                TempSum += TempOverLast24Hours[j];
              }
              AvgTemp = TempSum / 24;






              int n_average = 15;
              // Averaging 15 different acceleration data to determine when the object tilts
              AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
              AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
              AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

              if (CurrentTime - PreviousTime > 200) { // 0.3g = 27deg tilt angle


             
                    matrix.fillScreen(0);
                  matrix.setCursor(z, 0);
                  matrix.printf("AVG TEMP: % .2f C", AvgTemp);
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


                  if (abs(AvgAccZ) > 0.4) //return back to main menu
                  {
                    break;
                  }

                }
              }

              if (AvgAccX > 0.4) { //tilting to the right
                case_code += 1;
                break;


              }


              else if ( AvgAccX < -0.4) { //tilting to the left
                case_code -= 1;
                break;
              }

            }






          case 2:


            if (abs(AvgAccX) < 0.4 || case_activated == true) {
              case_activated = true;



              M5.dis.displaybuff(Case_iii);

              if (M5.Btn.wasPressed()) {
                for (;;) {

                  CurrentTime = millis();

                  

                  M5.IMU.getAccelData(&accX, &accY, &accZ);
                  M5.IMU.getTempData(&temp);
                 
                    int n_average = 15;
                  // Averaging 15 different acceleration data to determine when the object tilts
                  AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
                  AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
                  AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;
                  


                  Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

                  

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


                  if (abs(AvgAccZ) > 0.4) //return back to main menu
                  {
                    break;
                  }

                }
              }

              if (AvgAccX > 0.4) { //tilting to the right
                case_code += 1;
                break;


              }


              else if ( AvgAccX < -0.4) { //tilting to the left
                case_code -= 1;
                break;
              }

            }






          case 3:

           
            if (abs(AvgAccX) < 0.4 || case_activated == true) {
              case_activated = true;



              M5.dis.displaybuff(Case_iv);

              if (M5.Btn.wasPressed()) {
                for (;;) {

                 
                  Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);

                  int n_average = 15;
                  // Averaging 15 different acceleration data to determine when the object tilts
                  AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
                  AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
                  AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;

                  M5.IMU.getAccelData(&accX, &accY, &accZ);
                  M5.IMU.getTempData(&temp);

                  CurrentTime = millis();

                  if (CurrentTime - PreviousTime >= 12000) {
                    k = 0;
                    for (k = 0; k < 71; k++) {
                      if ((k % 15) != 0 || k == 0) {
                        if (TempGraph [k + 6] == 255) {
                          TempGraph[k + 3] = 0xff;
                        }
                        else if (TempGraph [k + 6] == 0) {
                          TempGraph[k + 3] = 0x00;
                        }
                      }


                      else {
                        TempGraph[k] = 0x00;

                      }
                      TempGraph [75] = 0x00;
                    }
                  }

                  if (temp >= 20 && temp < 30) {

                    TempGraph [75] = 0xff;

                  }


                  else if (temp >= 30 && temp < 35) {

                    TempGraph [60] = 0xff;

                  }

                  
                  else if (temp >= 35 && temp < 40) {
                    TempGraph[45] = 0xff;
                  }
                  else if (temp >= 40 && temp < 45) {
                    TempGraph [30] = 0xff;
                  }
                  else if (temp >= 45 && temp < 50) {
                    TempGraph[15] = 0xff;
                  }
                  PreviousTime = millis();

                 
                   






                  M5.dis.displaybuff(TempGraph);


                  if (abs(AvgAccZ) > 0.4) //return back to main menu
                  {
                    break;
                  }

                }
              }
              if (AvgAccX > 0.4) { //tilting to the right
                case_code += 1;

                break;

              }



              else if ( AvgAccX < -0.4) { //tilting to the left
                case_code -= 1;

                break;
              }
            }







          case 4:

            if (abs(AvgAccX) < 0.4 || case_activated == true) {
              case_activated = true;



              M5.dis.displaybuff(Case_v);

              if (M5.Btn.wasPressed()) {
                for (;;) {

                  CurrentTime = millis();

                  M5.IMU.getAccelData(&accX, &accY, &accZ);
                  M5.IMU.getTempData(&temp);




                  int n_average = 15;
                  // Averaging 15 different acceleration data to determine when the object tilts
                  AvgAccZ = ((AvgAccZ * (n_average - 1)) + accZ) / n_average;
                  AvgAccY = ((AvgAccY * (n_average - 1)) + accY) / n_average;
                  AvgAccX = ((AvgAccX * (n_average - 1)) + accX) / n_average;


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

                  if (abs(AvgAccZ) > 0.4) //return back to main menu
                  {
                    break;
                  }

                }
              }
              if (AvgAccX > 0.4) { //tilting to the right
                case_code = 0;

                break;

              }



              else if ( AvgAccX < -0.4) { //tilting to the left
                case_code -= 1;

                break;
              }
            }

          default:
            break;


          }

        }




        M5.update();

    }
