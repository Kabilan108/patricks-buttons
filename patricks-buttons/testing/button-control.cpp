/*
BUTTON CONTROLS

This sketch implements the control of buttons and LEDS using the Bounce2
library to perform debouncing. It serves as a proof of concept for the
button control for the project.
*/

// Libraries
#include <Arduino.h>
#include <Bounce2.h>

// Define constants
#define BUTTON_ON_OFF 3
#define BUTTON_CH_UP 4
#define BUTTON_CH_DOWN 5
#define LED_ON_OFF 11
#define LED_CH_UP 12
#define LED_CH_DOWN 13
#define BAUD_RATE 9600

// Button objects
Bounce onOffButton = Bounce();
Bounce chUpButton = Bounce();
Bounce chDownButton = Bounce();


void setup() {
    // Start serial
    Serial.begin(BAUD_RATE);
    
    // Attach the buttons to their pins
    onOffButton.attach(BUTTON_ON_OFF, INPUT);
    chUpButton.attach(BUTTON_CH_UP, INPUT);
    chDownButton.attach(BUTTON_CH_DOWN, INPUT);

    // Set debounce interval to 25ms
    onOffButton.interval(25);
    chUpButton.interval(25);
    chDownButton.interval(25);

    // Set the LEDs to output
    pinMode(LED_ON_OFF, OUTPUT);
    pinMode(LED_CH_UP, OUTPUT);
    pinMode(LED_CH_DOWN, OUTPUT);

    // Turn the LEDs off
    digitalWrite(LED_ON_OFF, LOW);
    digitalWrite(LED_CH_UP, LOW);
    digitalWrite(LED_CH_DOWN, LOW);

    // Print message to serial monitor
    Serial.println("Ready!");
}


void loop() {
    // Update the Bounce instances
    onOffButton.update();
    chUpButton.update();
    chDownButton.update();

    // Call code if buttons transition from LOW to HIGH (pressed)
    if (onOffButton.rose()) {
        digitalWrite(LED_ON_OFF, HIGH);
        Serial.println("On/Off button pressed");
    }
    if (chUpButton.rose()) {
        digitalWrite(LED_CH_UP, HIGH);
        Serial.println("Channel Up button pressed");
    }
    if (chDownButton.rose()) {
        digitalWrite(LED_CH_DOWN, HIGH);
        Serial.println("Channel Down button pressed");
    }

    // Turn the LEDs off if the buttons transition from HIGH to LOW (released)
    if (onOffButton.fell()) {
        digitalWrite(LED_ON_OFF, LOW);
    }
    if (chUpButton.fell()) {
        digitalWrite(LED_CH_UP, LOW);
    }
    if (chDownButton.fell()) {
        digitalWrite(LED_CH_DOWN, LOW);
    }

    // Wait 10ms before checking again
    delay(10);
}
