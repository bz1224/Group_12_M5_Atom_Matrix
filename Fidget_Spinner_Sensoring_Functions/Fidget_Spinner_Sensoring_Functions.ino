#include <M5Atom.h>

#include <FastLED.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "Group_12_Fidget_Spinner";
const char *password = "abcdefgh";

WiFiServer server(80);

#define count_interval 200
#define one_hour 10000
#define hrs_per_day 24

int per_hour_fidget_counter[hrs_per_day] = {0}; // Providing an array of counts per hour over the most recent 24 hours
float gyroX, gyroY, gyroZ1, gyroZ2; 
unsigned long CurrentTime, PreviousTime, CurrentHour, PreviousHour;

void setup() {
  
  M5.begin(true, false, true);
  M5.IMU.Init();

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
  
}

void loop() {
  
  // These functions collects number of fidgets in the most recent hour
  PreviousHour = millis();
  for (;CurrentHour - PreviousHour > one_hour;) {
    CurrentTime = millis();

    // This part of code lights up the LEDs when the spin is fast (strength indicator)
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ1);
    if (abs(gyroZ1) > 500) {
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


  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print(" <p>Fidget Spinner - Fidget Event Counter in the Latest 24 Hours (times per hour)</p>"); //INTERESTING PART 1
            client.print("Click <a href=\"/H\">here</a> to update fidget frequencies.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            // Printing the current collection of numbers of fidgets
            for (int j = 0;j < 24;j++) {
              client.print(23 - j);
              client.print(" hrs ago: ");
              client.print(per_hour_fidget_counter[j]);
              client.print(" fidgets.<br>");
            }
            
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          //INTERESTING PART 2
          Serial.println("I AM HIGH");
        }
        if (currentLine.endsWith("GET /L")) {
          //INTERESTING PART 3
          Serial.println("I AM LOW");

        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
