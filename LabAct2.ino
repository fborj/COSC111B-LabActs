int ledPins[5] = {11, 10, 9, 6, 5};
int numLeds = 5;

void setup() {
  int i = 0;
  while (i < numLeds) {
    pinMode(ledPins[i], OUTPUT);
    i++;
  }
}

void loop() {
  int brightness = 0;
  int fadeAmount = 50;

  int onIndex = 0;
  while (onIndex < numLeds) {
    brightness = 0;
    while (brightness <= 255) {
      analogWrite(ledPins[onIndex], brightness);
      brightness += fadeAmount;
      delay(20);
    }
    delay(1000);
    onIndex++;
  }

  int offIndex = 0;
  while (offIndex < numLeds) {
    brightness = 255;
    while (brightness >= 0) {
      analogWrite(ledPins[offIndex], brightness);
      brightness -= fadeAmount;
      delay(20);
    }
    delay(1000);
    offIndex++;
  }
}