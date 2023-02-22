/*
Button Controls
*/

// Include the Bounce2 library
#include <Bounce2.h>

// Define pins for the buttons
#define ON_OFF_BUTTON 3
#define CHUP_BUTTON 4
#define CHDOWN_BUTTON 5

// Define pins for the LEDs
#define ON_OFF_LED 11
#define CHUP_LED 12
#define CHDOWN_LED 13

// Create Bounce instances for each button
Bounce onOffButton = Bounce();
Bounce chUpButton = Bounce();
Bounce chDownButton = Bounce();


void setup() {
    // Start serial
    Serial.begin(9600);

    // Attach the buttons to their pins
    onOffButton.attach(ON_OFF_BUTTON, INPUT);
    chUpButton.attach(CHUP_BUTTON, INPUT);
    chDownButton.attach(CHDOWN_BUTTON, INPUT);

    // Set debounce interval to 25ms
    onOffButton.interval(25);
    chUpButton.interval(25);
    chDownButton.interval(25);

    // Set the LEDs to output
    pinMode(ON_OFF_LED, OUTPUT);
    pinMode(CHUP_LED, OUTPUT);
    pinMode(CHDOWN_LED, OUTPUT);

    // Turn the LEDs off
    digitalWrite(ON_OFF_LED, LOW);
    digitalWrite(CHUP_LED, LOW);
    digitalWrite(CHDOWN_LED, LOW);

    // Print a message to the serial monitor
    Serial.println("Ready!");
}


void loop() {
    // Update the Bounce instances
    onOffButton.update();
    chUpButton.update();
    chDownButton.update();

    // Call code if buttons transition from LOW to HIGH (pressed)
    if (onOffButton.rose()) {
        digitalWrite(ON_OFF_LED, HIGH);
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
        digitalWrite(ON_OFF_LED, LOW);
    }
    if (chUpButton.fell()) {
        digitalWrite(CHUP_LED, LOW);
    }
    if (chDownButton.fell()) {
        digitalWrite(CHDOWN_LED, LOW);
    }

    // Wait 10ms before checking again
    delay(10);
}
