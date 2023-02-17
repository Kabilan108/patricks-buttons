/*
Button Controls
*/

// Include the Bounce2 library
#include <Bounce2.h>

// Define the pins for the buttons
#define BUTTON_PIN 2
#define LED_PIN 13

// Track LED state
int ledState = LOW;

// Create a Bounce object
Bounce b = Bounce();


void setup() {
    // Attach the debouncer to a pin
    b.attach(BUTTON_PIN, INPUT);
    b.interval(25);  // Debounce interval in ms

    // Set the LED pin to output
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, ledState);  // Turn the LED off

    // Start serial
    Serial.begin(9600);
}


void loop() {
    // Update the Bounce instance
    b.update();

    // Call code if button transitions from LOW to HIGH
    if (b.rose()) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        Serial.println("Button pressed");
    }
}
