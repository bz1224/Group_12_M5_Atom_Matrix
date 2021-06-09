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
#define one_hour 3600000
#define hrs_per_day 24

int per_hour_fidget_counter[hrs_per_day] = {0}; // Providing an array of counts per hour over the most recent 24 hours
float accX, accY, accZ;
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

  PreviousHour = millis();
  PreviousTime = millis();
}

void loop() {

  CurrentHour = millis();
  CurrentTime = millis();

  if (CurrentTime - PreviousTime > count_interval) {
    M5.IMU.getAccelData(&accX, &accY, &accZ);

    // Horizontal spinning event criteria
    if (abs(accX) > 0.3 && abs(accY) > 0.3 && abs(accZ) > 0.9) {
      per_hour_fidget_counter[hrs_per_day - 1] += 1; // These functions collects number of fidgets in the most recent hour
      M5.dis.fillpix(0x00ff00); // Red colour
    }

    else {
      M5.dis.fillpix(0x000000); // Black screen
    }
    PreviousTime = millis();
  }

  // This part serves updating the counter array every hour past, the array is only holding a maximum of 24 data.
  if (CurrentHour - PreviousHour > one_hour) {
    for (int i = 0; i < hrs_per_day - 1; i++) {
      per_hour_fidget_counter[i] = per_hour_fidget_counter[i + 1];
    }
    per_hour_fidget_counter[hrs_per_day - 1] = 0;
    PreviousHour = millis();
  }

  // WiFi and webpage setting
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
            client.println();

            // Printing the current collection of numbers of fidgets
            for (int j = 0; j < 24; j++) {
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

        // Reflect in the serial port to see the webpage operation of updating current display
        if (currentLine.endsWith("GET /H")) {
          //INTERESTING PART 2
          Serial.println("Data updated.");
        }

      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
