//#include <M5Stack.h>
#include <M5Atom.h>
#include <FastLED.h>

float AvgAccX = 0.0F;
float AvgAccY = 0.0F;
float AvgAccZ = 0.0F;


// the setup routine runs once when M5Stack starts up
void setup(){

  // Initialize the M5Stack object
  M5.begin(true, false, true);

  //start with a black screen

  M5.dis.fillpix(0x0000);

}

// the loop routine runs over and over again forever
void loop() {
    // put your main code here, to run repeatedly:

    float accX = 0, accY = 0, accZ = 0;
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  int n_average=15;
  // Averaging 15 different acceleration data to determine when the object tilts
  AvgAccZ = ((AvgAccZ * (n_average-1))+accZ)/n_average;
  AvgAccY = ((AvgAccY * (n_average-1))+accY)/n_average;
  AvgAccX = ((AvgAccX * (n_average-1))+accX)/n_average;

  if (M5.Btn.wasPressed()){

    for (;;){
    //Write the code needed for showing the temperature when the button is pressed
    

    if(AvgAccZ > 0.7 && abs(AvgAccX) > 0.3){ // 0.3g = 0.27 deg tilt angle (perform the tasks below if the angle is greater than 0.27 degrees left or right

        //show the code needed to change game mode
      }


    
    
    }
  
 

  M5.update();
}
}
