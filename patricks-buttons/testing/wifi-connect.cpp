/*
    Wifi API Testing

    This sketch connects to a WiFi network and attempts to submit API
    requests.
*/

#include <Arduino.h>
// #include <ESP8266WiFi.h>
#include <SoftwareSerial.h>


// ################################# CONFIG ##################################

// Define Pins
#define RX 2
#define TX 3
#define CONNECTED 12
#define FAILED 11

// Wifi Credentials
String ssid     = "kabil"; //Wifi SSID
String password = "123456789"; //Wifi Password

// ASKSENSORS API host config
String host = "api.asksensors.com";  // API host name
String apiKey = ".............";     // API Key
String port = "80";                  // port

// Variable definitions and declarations
SoftwareSerial AT(RX,TX);      // Software Serial for ESP8266
int AT_cmd_time;               // AT command time
boolean AT_cmd_flag = false;   // AT command result
const unsigned int writeInterval = 25000; // write interval (in ms)
void sendATcmd(String AT_cmd, int AT_cmd_maxTime, char readReplay[]);


// ################################## SETUP ##################################

void setup() {
    // Begin serial for Arduino and AT commands
    Serial.begin(9600);
    AT.begin(9600);

    // Pin modes
    pinMode(CONNECTED, OUTPUT);

    // Welcome messages
    Serial.println("#-----------------------------------------------#");
    Serial.println("#         WELCOME TO PATRICK'S BUTTONS!         #");
    Serial.println("#-----------------------------------------------#");
    Serial.println(" ");

    // Initialize AT commands with ESP8266
    Serial.println("Initiate AT commands with ESP8266: ");

    // Test AT command
    sendATcmd("AT", 5, "OK");

    // Set ESP8266 to Station mode
    sendATcmd("AT+CWMODE=1", 5, "OK");

    // Connect to WiFi
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    sendATcmd("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", 20, "OK");
    digitalWrite(CONNECTED, HIGH);
}


// ################################# LOOP ##################################

void loop() {

    // Check if connected to WiFi

//  // Create the URL for the request
//   String url = "GET /write/";
//   url += apiKeyIn;
//   url += "?module1=";
//   url += random(10, 100);
//   Serial.println("*****************************************************");
//   Serial.println("********** Open TCP connection ");
//   sendATcmd("AT+CIPMUX=1", 10, "OK");
//   sendATcmd("AT+CIPSTART=0, \"TCP\",\"" + host +"\"," + port, 20, "OK");
//   sendATcmd("AT+CIPSEND=0," + String(url.length() + 4), 10, ">");
  
//   Serial.print("********** requesting URL: ");
//   Serial.println(url);
//   AT.println(url);
//   delay(2000);
//   sendATcmd("AT+CIPCLOSE=0", 10, "OK");
  
//   Serial.println("********** Close TCP Connection ");
//   Serial.println("*****************************************************");
  
//   delay(writeInterval);   // delay
}


// ################################ FUNCTIONS ################################


// sendATcmd
// This function sends an AT command to the ESP8266 and waits for a response
// before returning a result.
void sendATcmd(String cmd, int timeout, char readReply[]) {
    // Print the AT command to the serial monitor
    Serial.print("AT command: ");
    Serial.println(cmd);

    // Send the AT command to the ESP8266 and wait for a response
    while (AT_cmd_time < timeout) {
        AT.println(cmd);
        if (AT.find(readReply)) {
            AT_cmd_flag = true;
            break;
        }
        AT_cmd_time++;
    }

    // Print the result of the AT command
    Serial.print("...Result: ");
    if (AT_cmd_flag == true) {
        Serial.println("DONE");
        AT_cmd_time = 0;
    } else {
        Serial.println("FAILED");
        AT_cmd_time = 0;
    }

    // Reset the flag
    AT_cmd_flag = false;
}
