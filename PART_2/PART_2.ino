#include <M5Stack.h>

float AvgAccX = 0.0F;
float AvgAccY = 0.0F;
float AvgAccZ = 0.0F;


// the setup routine runs once when M5Stack starts up
void setup(){

  // Initialize the M5Stack object
  M5.begin(true, false, true);

  //start with a black screen

  fillScreen(cBLACK);
}

// the loop routine runs over and over again forever
void loop() {
    // put your main code here, to run repeatedly:

    float accX = 0, accY = 0, accZ = 0;
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  // Averaging the acceleration data to determine when the object tilts
  accZ_avg = ((accZ_avg * (n_average-1))+accZ)/n_average;
  accY_avg = ((accY_avg * (n_average-1))+accY)/n_average;
  accX_avg = ((accX_avg * (n_average-1))+accX)/n_average;

  if (M5.Btn.wasPressed()){

    for (;;){
    //Write the code needed for showing the temperature when the button is pressed
    

    if(accZ_avg > 0.7 && abs(accX_avg) > 0.3){ // 0.3g = 0.27 deg tilt angle (perform the tasks below if the angle is greater than 0.27 degrees left or right

        //show the code needed to change game mode
      }


    
    
    }
  
 

  M5.update();
}
}

  

 
}
