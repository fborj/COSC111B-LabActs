#define PHOTORESISTOR_PIN A2
#define LED_PIN 8            // LED pin is Pin 8

const int BRIGHTNESS_THRESHOLD = 220; // Required threshold

// State variable for the latching alarm status
bool alarm_active = false; 


void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  // pinMode(BUZZER_PIN, OUTPUT); // Buzzer pin removed since it's not used

  Serial.println("--- Serial Controlled Alarm Initialized ---");
  Serial.print("Monitoring Photoresistor on A2. Threshold: ");
  Serial.println(BRIGHTNESS_THRESHOLD);
  Serial.println("LED on Pin 8 will blink when threshold is met.");
  Serial.println("Enter 'stop' (case insensitive) to disable the blinking.");
  Serial.println("-------------------------------------------");
  
  // digitalWrite(BUZZER_PIN, LOW); // Buzzer code removed
  // noTone(BUZZER_PIN);
}

void loop() {
  // Check for incoming Serial Data
  checkSerialInput();

  // Read Sensor Value
  int currentBrightness = readBrightness();
  Serial.print("Brightness: ");
  Serial.println(currentBrightness); 

  // Check and Set Latching State (The blinking MUST continue even after threshold is below 220)
  if (currentBrightness >= BRIGHTNESS_THRESHOLD) {
    alarm_active = true; 
  }

  // Alarm Action (Execution)
  if (alarm_active) {
    // Blink the LED on pin 8 with a 100ms delay
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  } else {
    // If alarm_active is false ('stop' was received), ensure LED is off
    digitalWrite(LED_PIN, LOW);
  }
  
  // A small delay to ensure the main loop doesn't run too fast
  delay(10); 
}

// Function to read brightness
int readBrightness() {
  return analogRead(PHOTORESISTOR_PIN);
}

// Function to check and process serial input
void checkSerialInput() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    
    input.toLowerCase(); 
    input.trim();

    // Check if the received word is "stop"
    if (input == "stop") {
      alarm_active = false; // Stop the blinking
      Serial.println("Alarm stopped by Serial Command.");
      digitalWrite(LED_PIN, LOW); // Turn LED off immediately
    }
  }
}