#include <Arduino.h>

#define BUTTON_PIN 3
#define LED_PIN 13


byte lastButtonState = LOW;
unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;


void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}


void checkPush(int pin) {
    if (digitalRead(pin) == HIGH) {
        Serial.println("Button pressed");
        digitalWrite(LED_PIN, HIGH);
    } else {
        Serial.println("Button released");
        digitalWrite(LED_PIN, LOW);
    }
}

void loop() {
    if (millis() - lastTimeButtonStateChanged > debounceDuration) {
        byte buttonState = digitalRead(BUTTON_PIN);
        if (buttonState != lastButtonState) {
            lastTimeButtonStateChanged = millis();
            lastButtonState = buttonState;

            checkPush(BUTTON_PIN);
        }
    }
}