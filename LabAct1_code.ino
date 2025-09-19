int ledPins[5] = {12, 11, 10, 9, 8};

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Chasing effect: LEDs turn ON one by one
  for (int x = 0; x < 5; x++) {
    digitalWrite(ledPins[x], HIGH);
    delay(200); // Shorter delay for a faster "chasing" feel
  }

  // Chasing effect: LEDs turn OFF one by one
  for (int y = 0; y < 5; y++) {
    digitalWrite(ledPins[y], LOW);
    delay(200); // Shorter delay for a faster "chasing" feel
  }
}