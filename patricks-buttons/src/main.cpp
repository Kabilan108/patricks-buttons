#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>



// #include <Arduino.h>
// #include <SoftwareSerial.h>

// const byte rxPin = 2;
// const byte txPin = 3;

// SoftwareSerial ESP8266 (rxPin, txPin);

// unsigned long lastTimeMillis = 0;

// int AT_cmd_time;               // AT command time
// boolean AT_cmd_flag = false;   // AT command result

// void setup() {
//   Serial.begin(9600);   
//   ESP8266.begin(9600);
//   delay(2000);
//   String ssid     = "kabil"; //Wifi SSID
//   String password = "123456789"; //Wifi Password
//   Serial.print("Connecting to WiFi: ");
//   Serial.println(ssid);
//   ESP8266.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
//   pinMode(13, OUTPUT);
//     digitalWrite(13, HIGH);
// }

// void printResponse() {
//   while (ESP8266.available()) {
//     Serial.println(ESP8266.readStringUntil('\n')); 
//   }
// }

// void loop() {

//   if (millis() - lastTimeMillis < 3000) {
//     lastTimeMillis = millis();

//     ESP8266.println("AT+CIPMUX=1");
//     delay(1000);
//     printResponse();

//     ESP8266.println("AT+CIPSTART=4,\"TCP\",\"192.168.6.216\",8000");
//     delay(1000);
//     printResponse();

//     // String cmd = "GET / HTTP/1.1\r\nHost: 192.168.6.216\r\nConnection: close\r\n\r\n";
//     String cmd = "GET / HTTP/1.1\r\nHost: 192.168.6.216\r\n";
//     ESP8266.println("AT+CIPSEND=4," + String(cmd.length() + 4));
//     delay(1000);
//     printResponse();

//     ESP8266.println(cmd);
//     delay(1000);
//     ESP8266.println(""); 
//   }

//   if (ESP8266.available()) {
//     Serial.write(ESP8266.read());
//   }

// }

// #include <Arduino.h>
// #include <ESP

// #define LED 13

// void setup() {
//     // initialize digital pin LED_1 as an output.
//     pinMode(LED, OUTPUT);
// }

// // the loop function runs over and over again forever
// void loop() {
//     digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
//     delay(1000);                      // wait for a second
//     digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
//     delay(1000);                      // wait for a second
// }



// /*
//     PATRICK'S BUTTONS
// */

// #include <Arduino.h>
// #include <Bounce2.h>
// #include <SoftwareSerial.h>


// // ################################# CONFIG ##################################

// // Pins for Wifi Connection
// #define RX 5
// #define TX 6
// #define CONNECTED 12

// // Pin for error state
// #define ERROR 11

// // Pins for Buttons
// #define ONOFF  4
// #define CHUP   3
// #define CHDOWN 2

// // TODO: These pins should connect to haptic motors (maybe amplifiers?)
// // Pins for Button LEDs
// #define ONOFF_LED  10
// #define CHUP_LED   9
// #define CHDOWN_LED 8

// // Baud rate for serial communication
// #define BAUD_RATE 9600

// // Debounce interval for buttons
// #define DEBOUNCE_INTERVAL 25

// // Wifi Credentials
// String ssid     = "kabil"; //Wifi SSID
// String password = "123456789"; //Wifi Password

// // ASKSENSORS API host config
// String host = "api.asksensors.com";  // API host name
// String apiKey = ".............";     // API Key
// String port = "80";                  // port

// // Variable definitions and declarations (Wifi stuff)
// SoftwareSerial AT(RX,TX);      // Software Serial for ESP8266
// int AT_cmd_time;               // AT command time
// boolean AT_cmd_flag = false;   // AT command result
// const unsigned int writeInterval = 25000; // write interval (in ms)
// void sendATcmd(String AT_cmd, int AT_cmd_maxTime, char readReplay[]);

// // Button objects
// Bounce onOffButton = Bounce();
// Bounce chUpButton = Bounce();
// Bounce chDownButton = Bounce();


// // ################################## SETUP ##################################

// void setup() {
//     // Begin serial for Arduino and AT commands
//     Serial.begin(9600);
//     AT.begin(9600);

//     // Attach the buttons to their pins
//     onOffButton.attach(ONOFF, INPUT);
//     chUpButton.attach(CHUP, INPUT);
//     chDownButton.attach(CHDOWN, INPUT);

//     // Set debounce interval to 25ms
//     onOffButton.interval(DEBOUNCE_INTERVAL);
//     chUpButton.interval(DEBOUNCE_INTERVAL);
//     chDownButton.interval(DEBOUNCE_INTERVAL);

//     // Pin modes
//     pinMode(CONNECTED, OUTPUT);
//     pinMode(ERROR, OUTPUT);
//     pinMode(ONOFF_LED, OUTPUT);
//     pinMode(CHUP_LED, OUTPUT);
//     pinMode(CHDOWN_LED, OUTPUT);

//     // Turn the button LEDs off
//     digitalWrite(ONOFF_LED, LOW);
//     digitalWrite(CHUP_LED, LOW);
//     digitalWrite(CHDOWN_LED, LOW);

//     // Welcome messages
//     Serial.println("#-----------------------------------------------#");
//     Serial.println("#         WELCOME TO PATRICK'S BUTTONS!         #");
//     Serial.println("#-----------------------------------------------#");
//     Serial.println(" ");

//     // Initialize AT commands with ESP8266
//     Serial.println("Initiate AT commands with ESP8266: ");

//     // Test AT command
//     sendATcmd("AT", 5, "OK");

//     // Set ESP8266 to Station mode
//     sendATcmd("AT+CWMODE=1", 5, "OK");

//     // Connect to WiFi
//     Serial.print("Connecting to WiFi: ");
//     Serial.println(ssid);
//     sendATcmd("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", 20, "OK");
//     digitalWrite(CONNECTED, HIGH);
// }


// // ################################# LOOP ##################################

// void loop() {

//     // Update the buttons
//     onOffButton.update();
//     chUpButton.update();
//     chDownButton.update();

//     // Call code if buttons transition from LOW to HIGH (pressed)
//     if (onOffButton.rose()) {
//         digitalWrite(ONOFF_LED, HIGH);
//         Serial.println("On/Off button pressed");
//     }
//     if (chUpButton.rose()) {
//         digitalWrite(CHUP_LED, HIGH);
//         Serial.println("Channel Up button pressed");
//     }
//     if (chDownButton.rose()) {
//         digitalWrite(CHDOWN_LED, HIGH);
//         Serial.println("Channel Down button pressed");
//     }

//     // Turn the LEDs off if the buttons transition from HIGH to LOW (released)
//     if (onOffButton.fell()) {
//         digitalWrite(ONOFF_LED, LOW);
//     }
//     if (chUpButton.fell()) {
//         digitalWrite(CHUP_LED, LOW);
//     }
//     if (chDownButton.fell()) {
//         digitalWrite(CHDOWN_LED, LOW);
//     }

//     // Check if connected to WiFi

// //  // Create the URL for the request
// //   String url = "GET /write/";
// //   url += apiKeyIn;
// //   url += "?module1=";
// //   url += random(10, 100);
// //   Serial.println("*****************************************************");
// //   Serial.println("********** Open TCP connection ");
// //   sendATcmd("AT+CIPMUX=1", 10, "OK");
// //   sendATcmd("AT+CIPSTART=0, \"TCP\",\"" + host +"\"," + port, 20, "OK");
// //   sendATcmd("AT+CIPSEND=0," + String(url.length() + 4), 10, ">");
  
// //   Serial.print("********** requesting URL: ");
// //   Serial.println(url);
// //   AT.println(url);
// //   delay(2000);
// //   sendATcmd("AT+CIPCLOSE=0", 10, "OK");
  
// //   Serial.println("********** Close TCP Connection ");
// //   Serial.println("*****************************************************");
  
// //   delay(writeInterval);   // delay
// }


// // ################################ FUNCTIONS ################################


// // sendATcmd
// // This function sends an AT command to the ESP8266 and waits for a response
// // before returning a result.
// void sendATcmd(String cmd, int timeout, char readReply[]) {
//     // Print the AT command to the serial monitor
//     Serial.print("AT command: ");
//     Serial.println(cmd);

//     // Send the AT command to the ESP8266 and wait for a response
//     while (AT_cmd_time < timeout) {
//         AT.println(cmd);
//         if (AT.find(readReply)) {
//             AT_cmd_flag = true;
//             break;
//         }
//         AT_cmd_time++;
//     }

//     // Print the result of the AT command
//     Serial.print("...Result: ");
//     if (AT_cmd_flag == true) {
//         Serial.println("DONE");
//         AT_cmd_time = 0;
//     } else {
//         Serial.println("FAILED");
//         AT_cmd_time = 0;
//     }

//     // Reset the flag
//     AT_cmd_flag = false;
// }
