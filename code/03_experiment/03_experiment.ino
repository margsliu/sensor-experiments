// Experiment 3: Temperature/Humidity sensor and two-colour LED indicator
// Description: LED shows you if the sensor detects "warming up" or "cooling down"
// Modules Used: Temperature and humidity sensor, Two-color LED
// Libraries Used: DHT Sensor Library by Adafruit
// Comments: I used some of the DHT Sensor library Example code and comments (DHTester.ino) and incorporated my LED portion of this experiment.

// Set up Temperature and Humidity Module library and declare module model
#include <DHT.h> 
#define DHTTYPE DHT11   // DHT 11

// Assign component groupings to Teensy 4.0 pins
#define TEMP_AND_HUMIDITY_MODULE 22
DHT dht(TEMP_AND_HUMIDITY_MODULE, DHTTYPE);

#define TWO_COLOR_LED_MODULE_RED 15
#define TWO_COLOR_LED_MODULE_GREEN 14

const bool USE_FAHRENHEIT = true;

float previousHumidity;
float currentHumidity;
float previousTemperature;
float currentTemperatureF;
float previousHeatIndexF;
float currentHeatIndexF;

const int GREEN_BRIGHTNESS = 150;
const int MIN_ALLOWED_RED_BRIGHTNESS = 0;
const int MAX_ALLOWED_RED_BRIGHTNESS = 255;
int redBrightness = MIN_ALLOWED_RED_BRIGHTNESS;

void setup() {
  Serial.begin(9600);
  pinMode(TWO_COLOR_LED_MODULE_RED, OUTPUT);
  pinMode(TWO_COLOR_LED_MODULE_GREEN, OUTPUT);
  analogWrite(TWO_COLOR_LED_MODULE_GREEN, GREEN_BRIGHTNESS);
  analogWrite(TWO_COLOR_LED_MODULE_RED, redBrightness);
  dht.begin();
}

void loop() {

  /* Get Temperature and Humidity readings, convert to heat index: */

  // According to the docs, "reading temperature or humidity takes about 250 milliseconds"
  delay(400);
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  currentHumidity = dht.readHumidity();
  currentTemperatureF = dht.readTemperature(USE_FAHRENHEIT);
  // Check if any reads failed and exit early (to try again)
  if (isnan(currentHumidity) || isnan(currentTemperatureF)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Heat index in Fahrenheit (the default)
  currentHeatIndexF = dht.computeHeatIndex(currentTemperatureF, currentHumidity);

  /* LED provides visual feedback about the sensor "warming up" (more red) or "cooling down" (less red) */

  if (currentHeatIndexF > previousHeatIndexF) {
    redBrightness += 10;
    if (redBrightness > MAX_ALLOWED_RED_BRIGHTNESS) {
      redBrightness = MAX_ALLOWED_RED_BRIGHTNESS;
    }
  } else if (currentHeatIndexF < previousHeatIndexF) {
    redBrightness -= 15;
    if (redBrightness < MIN_ALLOWED_RED_BRIGHTNESS ) {
      redBrightness = MIN_ALLOWED_RED_BRIGHTNESS;
    }
  }
  analogWrite(TWO_COLOR_LED_MODULE_RED, redBrightness);

  Serial.print(F("Humidity: "));
  Serial.print(currentHumidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(currentTemperatureF);
  Serial.print(F("°F  Heat index: "));
  Serial.print(currentHeatIndexF);
  Serial.println(F("°F"));

  previousHeatIndexF = currentHeatIndexF;
}