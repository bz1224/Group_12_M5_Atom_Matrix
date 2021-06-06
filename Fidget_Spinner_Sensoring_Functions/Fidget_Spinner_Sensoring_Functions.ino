#include <M5Atom.h>

#include <FastLED.h>

// Not sure what libraries related to webpage/wifi are missing, please add on

#define count_interval 200
#define one_hour 3600000
#define hrs_per_day 24

int per_hour_fidget_counter[hrs_per_day] = {0}; // Providing an array of counts per hour over the most recent 24 hours
float gyroX, gyroY, gyroZ1, gyroZ2; 
unsigned long CurrentTime, PreviousTime, CurrentHour, PreviousHour;

void setup() {
  // Some functions about webpage/wifi may be necessary

  M5.begin(true, false, true);
  M5.IMU.Init();
  
}

void loop() {
  // Again, some functions about webpage/wifi may be necessary

  // These functions collects number of fidgets in the most recent hour
  PreviousHour = millis();
  for (;CurrentHour - PreviousHour > one_hour;) {
    CurrentTime = millis();

    // This part of code lights up the LEDs when the spin is fast (strength indicator)
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ1);
    if (abs(gyroZ1) > 1000) {
      M5.dis.fillpix(0x00ff00); // Correct Red Colour in GRB Order
    }

    else {
      M5.dis.fillpix(0x000000); // Black screen
    }

    // This part of code records increase in absolute angular velocity (i.e. a fidget event)
    if (CurrentTime - PreviousTime > count_interval) {
      M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ2);
      // Greater absolute angular velocity around Z axis when a fidget event occurs
      if (abs(gyroZ2) > abs(gyroZ1)) {
        per_hour_fidget_counter[hrs_per_day - 1] += 1;
      }
      PreviousTime = millis();
    }
    CurrentHour = millis(); 
  }

  // This loop overrights all elements in the counter array, capping the number of data entry at 24
  for (int i = 0;i < hrs_per_day - 1;i++) {
    per_hour_fidget_counter[i] = per_hour_fidget_counter[i+1];
  }

  // This array shall be uploaded online to reflect fidgeting event during the past 24 hours.

  
  M5.update();
}
