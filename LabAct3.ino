// ----------------------------------------------------------------------
// 1. PIN DEFINITIONS using #define
// ----------------------------------------------------------------------
#define THERMISTOR_PIN A0
#define PHOTORESISTOR_PIN A2
#define LED_PIN 12      // Red LED, fast blink
#define BUZZER_PIN 11   // Buzzer/Speaker, tone

// ----------------------------------------------------------------------
// 2. THRESHOLD DEFINITIONS using const
// ----------------------------------------------------------------------
const float TEMPERATURE_THRESHOLD = 50.0; // Celsius
// FINAL ADJUSTMENT for Tinkercad ambient light: Set very high (900)
// This should prevent the ambient light from triggering the alarm.
const int BRIGHTNESS_THRESHOLD = 900;     // Raw Analog Value (0-1023)

// ----------------------------------------------------------------------
// 3. THERMISTOR COEFFICIENTS
// ----------------------------------------------------------------------
const float THERMISTOR_NOMINAL = 10000;    
const float TEMPERATURE_NOMINAL = 25;      
const float B_COEFFICIENT = 3950;          
const float SERIES_RESISTOR = 10000;       

// Function Prototypes
float readTemperature();
int readBrightness();
void setAlarm(bool fireDetected);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read the sensor values
  float currentTemp = readTemperature();
  int currentBrightness = readBrightness();

  // Check the fire condition: Temperature (A0) AND Brightness (A2) must exceed the thresholds
  bool fireDetected = (currentTemp >= TEMPERATURE_THRESHOLD) && (currentBrightness >= BRIGHTNESS_THRESHOLD);

  // Control the alarm system
  setAlarm(fireDetected);

  delay(500);
}

// ----------------------------------------------------------------------
// 4. TEMPERATURE READING FUNCTION
// ----------------------------------------------------------------------
/**
 * @brief Reads the thermistor and converts the reading to Celsius.
 * @return The temperature in Celsius.
 */
float readTemperature() {
  int analogValue = analogRead(THERMISTOR_PIN);
  float resistance;
  resistance = SERIES_RESISTOR * (1023.0 / analogValue - 1.0);
  float steinhart;
  steinhart = resistance / THERMISTOR_NOMINAL;
  steinhart = log(steinhart);
  steinhart /= B_COEFFICIENT;
  steinhart += 1.0 / (TEMPERATURE_NOMINAL + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15; 
  return steinhart;
}

// ----------------------------------------------------------------------
// 5. BRIGHTNESS READING FUNCTION
// ----------------------------------------------------------------------
/**
 * @brief Reads the raw analogue value from the photoresistor (LDR).
 * @return The raw analogue value (0-1023).
 */
int readBrightness() {
  return analogRead(PHOTORESISTOR_PIN);
}

// ----------------------------------------------------------------------
// 6. ALARM CONTROL FUNCTION
// ----------------------------------------------------------------------
void setAlarm(bool fireDetected) {
  if (fireDetected) {
    // LED ON and Blinking
    digitalWrite(LED_PIN, HIGH);
    // Buzzer ON 
    tone(BUZZER_PIN, 3000); 

    delay(100); 

    // LED OFF
    digitalWrite(LED_PIN, LOW);

    delay(100); 
    
  } else {
    // Turn off both alarms
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN); 
  }
}