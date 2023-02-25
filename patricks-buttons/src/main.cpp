/*
    PATRICK'S BUTTONS
*/

#include <Arduino.h>
#include <Bounce2.h>
#include <SoftwareSerial.h>


// ################################ CONSTANTS ################################

// Arduino pin numbers
#define CHDOWN_BTN 2
#define CHUP_BTN   3
#define ONOFF_BTN  4
#define RX         5
#define TX         6
#define CHDOWN_LED 8
#define CHUP_LED   9
#define ONOFF_LED  10
#define ERROR      11
#define CONNECTED  12

#define BAUD_RATE 9600                    // baud rate for serial communication
#define DEBOUNCE_INTERVAL 25              // debounce interval (in ms)

const String ssid     = "kabil";          // Wifi SSID
const String password = "123456789";      // Wifi Password
const String host     = "192.168.6.216";  // API host name
const String port     = "80";             // Port

SoftwareSerial ESP8266(RX,TX);            // Software serial for ESP8266

int AT_cmd_time;                          // AT command time
boolean AT_cmd_flag = false;              // AT command result
const unsigned int writeInterval = 5000;  // write interval (in ms)

Bounce onOffButton = Bounce();            // on/off button
Bounce chUpButton = Bounce();             // channel up button
Bounce chDownButton = Bounce();           // channel down button

String request = "";
void sendAT(String cmd, int timeout, char readReply[]);
void sendRequest(String request);


// ################################## SETUP ##################################

void setup() {
    // Begin serial for Arduino and ESP8266
    Serial.begin(BAUD_RATE);
    ESP8266.begin(BAUD_RATE);
    Serial.println("Setting things up...");

    // LED pin modes
    pinMode(CONNECTED, OUTPUT);
    pinMode(ERROR, OUTPUT);
    pinMode(ONOFF_LED, OUTPUT);
    pinMode(CHUP_LED, OUTPUT);
    pinMode(CHDOWN_LED, OUTPUT);

    // Turn the LEDs off
    digitalWrite(CONNECTED, LOW);
    digitalWrite(ERROR, LOW);
    digitalWrite(ONOFF_LED, LOW);
    digitalWrite(CHUP_LED, LOW);
    digitalWrite(CHDOWN_LED, LOW);

    // Attach the buttons to their pins
    onOffButton.attach(ONOFF_BTN, INPUT);
    chUpButton.attach(CHUP_BTN, INPUT);
    chDownButton.attach(CHDOWN_BTN, INPUT);

    // Set debounce interval
    onOffButton.interval(DEBOUNCE_INTERVAL);
    chUpButton.interval(DEBOUNCE_INTERVAL);
    chDownButton.interval(DEBOUNCE_INTERVAL);

    // Initialize the ESP8266
    Serial.println("Initiate AT commands with ESP8266: ");
    sendAT("AT", 5, "OK");            // Test AT startup
    sendAT("AT+CWMODE=1", 5, "OK");   // Set ESP8266 to Station mode

    // Connect to WiFi
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    sendAT("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"", 30, "OK");
    digitalWrite(CONNECTED, HIGH);
}


// ################################# LOOP ##################################

void loop() {
    // Update the buttons
    onOffButton.update();
    chUpButton.update();
    chDownButton.update();

    // Call code if buttons transition from LOW to HIGH (pressed)
    if (onOffButton.rose()) {
        digitalWrite(ONOFF_LED, HIGH);
        Serial.println("On/Off button pressed");
    }
    if (chUpButton.rose()) {
        digitalWrite(CHUP_LED, HIGH);
        Serial.println("Channel Up button pressed");
    }
    if (chDownButton.rose()) {
        digitalWrite(CHDOWN_LED, HIGH);
        Serial.println("Channel Down button pressed");
    }

    // Turn the LEDs off if the buttons transition from HIGH to LOW (released)
    if (onOffButton.fell()) {
        digitalWrite(ONOFF_LED, LOW);
    }
    if (chUpButton.fell()) {
        digitalWrite(CHUP_LED, LOW);
    }
    if (chDownButton.fell()) {
        digitalWrite(CHDOWN_LED, LOW);
    }

    request = "";
    sendRequest(request);


    // Create URL for the request
    // String url = "GET /write/";
    // url += apiKey;
    // url += "?module1=";
    // url += random(10, 100);
    // String url = "GET / HTTP/1.1\r\nHost: ";
    // url += host;
    // url += "\r\n";
    // url += "Connection: close\r\n\r\n";
    // String url = "GET /"+ request + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
    // Serial.println("*****************************************************");
    // Serial.println("***              Open TCP connection              ***");
    
    // // Open TCP connection
    // sendAT("AT+CIPMUX=1", 10, "OK");

    // // Start TCP connection
    // sendAT("AT+CIPSTART=0,\"TCP\",\"" + host +"\"," + port, 20, "OK");

    // // Send data
    // sendAT("AT+CIPSEND=0," + String(url.length() + 4), 10, ">");

    // // Send URL
    // Serial.print("***              requesting URL: ");
    // Serial.println(url);
    // AT.println(url);
    // delay(2000);
    // sendAT("AT+CIPCLOSE=0", 10, "OK");

    // Serial.println("***              Close TCP connection             ***");
    // Serial.println("*****************************************************");

    // // Wait for writeInterval
    // delay(writeInterval);
}


// ################################ FUNCTIONS ################################

void sendAT(String cmd, int timeout, char readReply[]) {
    /*
    This function sends an AT command to the ESP8266 and waits for a response
    before returning a result.
    */

    // Print the AT command to the serial monitor
    Serial.print("AT command: ");
    Serial.println(cmd);

    // Send the AT command to the ESP8266 and wait for a response
    while (AT_cmd_time < timeout) {
        ESP8266.println(cmd);
        if (ESP8266.find(readReply)) {
            AT_cmd_flag = true;
            break;
        }
        AT_cmd_time++;
    }

    // Print the result of the AT command
    Serial.print("...Result: ");
    if (AT_cmd_flag == true) {
        Serial.println("DONE");
    } else {
        Serial.println("FAILED");
    }

    // Reset the flag and time
    AT_cmd_time = 0;
    AT_cmd_flag = false;
}

void sendRequest(String request) {
    /*
    Send a request to the API
    */

    // Create URL for the request
    String url = "GET /" + request + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
    url += "Connection: close\r\n\r\n";

    // Open TCP connection
    Serial.println("--- Opening TCP connection ---");
    sendAT("AT+CIPMUX=1", 10, "OK");
    sendAT("AT+CIPSTART=0,\"TCP\",\"" + host +"\"," + port, 20, "OK");

    // Send data
    sendAT("AT+CIPSEND=0," + String(url.length() + 4), 10, ">");

    // Send URL
    Serial.print("--- Requesting URL: ");
    Serial.println(url);
    ESP8266.println(url);

    // Close TCP connection
    delay(2000);
    sendAT("AT+CIPCLOSE=0", 10, "OK");
    Serial.println("--- Closing TCP connection ---");
}
