#define OUTPUT_PIN 13
#define OUTPUT_PIN2 12

void setup() {
  // initialize digital pin OUTPUT_PIN as an output.
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(OUTPUT_PIN2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(OUTPUT_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(OUTPUT_PIN2, HIGH);
  delay(1000);                      // wait for a second
  digitalWrite(OUTPUT_PIN, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(OUTPUT_PIN2, LOW);
  delay(1000);                      // wait for a second
}