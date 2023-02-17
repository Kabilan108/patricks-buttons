#define BUTTON_PIN 3
#define LED_PIN 12


byte lastButtonState = LOW;
unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;


void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}


void loop() {
    if (millis() - lastTimeButtonStateChanged > debounceDuration) {
        byte buttonState = digitalRead(BUTTON_PIN);
        if (buttonState != lastButtonState) {
            lastTimeButtonStateChanged = millis();
            lastButtonState = buttonState;

            if (buttonState == LOW) {
                // do an action, for example print on Serial
                Serial.println("Button released");
                digitalWrite(LED_PIN, LOW);
            } else{
                digitalWrite(LED_PIN, HIGH);
            }
        }
    }
}
