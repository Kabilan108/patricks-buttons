#define BUTTON_PIN_1 3
#define LED_PIN_1 11
#define BUTTON_PIN_2 4
#define LED_PIN_2 12
#define BUTTON_PIN_3 5
#define LED_PIN_3 13


byte lastButtonState1 = LOW;
byte lastButtonState2 = LOW;
byte lastButtonState3 = LOW;
unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButton1StateChanged = 0;
unsigned long lastTimeButton2StateChanged = 0;
unsigned long lastTimeButton3StateChanged = 0;


void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN_1, INPUT);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(BUTTON_PIN_2, INPUT);
    pinMode(LED_PIN_2, OUTPUT);
    pinMode(BUTTON_PIN_3, INPUT);
    pinMode(LED_PIN_3, OUTPUT);
}


void checkPush(int buttonPin, int ledPin, byte lastButtonState) {
    if (digitalRead(buttonPin) == HIGH) {
        Serial.println("Button pressed");
        digitalWrite(ledPin, HIGH);
    } else {
        Serial.println("Button released");
        digitalWrite(ledPin, LOW);
    }
}


void loop() {
    if (millis() - lastTimeButton1StateChanged > debounceDuration) {
        byte buttonState1 = digitalRead(BUTTON_PIN_1);
        if (buttonState1 != lastButtonState1) {
            lastTimeButton1StateChanged = millis();
            lastButtonState1 = buttonState1;

            checkPush(BUTTON_PIN_1, LED_PIN_1, lastButtonState1);
        }
    }

    if (millis() - lastTimeButton2StateChanged > debounceDuration) {
        byte buttonState2 = digitalRead(BUTTON_PIN_2);
        if (buttonState2 != lastButtonState2) {
            lastTimeButton2StateChanged = millis();
            lastButtonState2 = buttonState2;

            checkPush(BUTTON_PIN_2, LED_PIN_2, lastButtonState2);
        }
    }

    if (millis() - lastTimeButton3StateChanged > debounceDuration) {
        byte buttonState3 = digitalRead(BUTTON_PIN_3);
        if (buttonState3 != lastButtonState3) {
            lastTimeButton3StateChanged = millis();
            lastButtonState3 = buttonState3;

            checkPush(BUTTON_PIN_3, LED_PIN_3, lastButtonState3);
        }
    }
}
