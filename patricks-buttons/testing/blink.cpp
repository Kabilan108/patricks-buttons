#include <Arduino.h>

#define LED_1 13
#define LED_2 12

void setup() {
    // initialize digital pin LED_1 as an output.
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(LED_1, HIGH);  // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED_2, HIGH);
    delay(1000);                      // wait for a second
    digitalWrite(LED_1, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(LED_2, LOW);
    delay(1000);                      // wait for a second
}
