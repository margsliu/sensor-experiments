// Experiment 2: Laser beam detection by photocell activates LED and buzzer
// Description: When photocell detects laser beam contact, LED turns on and passive buzzer sounds random tones until contact is broken.
// Modules Used: Photocell module, Laser module, Passive buzzer module

// Assign component groupings to Teensy 4.0 pins
const int LED_EXTERNAL = 23;
const int PHOTOCELL_MODULE = 22;
const int LASER_EMIT_MODULE = 0;
const int PASSIVE_BUZZER_MODULE = 1;

// Set LED on/off brightness
const int LED_EXTERNAL_OFF = 0;
const int LED_EXTERNAL_ON = 100;
// Set photocell laser detection threshold (~50 signal seemed appropriate enough to distinguish states)
const int LASER_CONTACT_THRESHOLD = 50;
// Set arbitrary frequency range of buzzer tone
const int MIN_FREQUENCY_HERTZ = 100;
const int MAX_FREQUENCY_HERTZ = 2000;

bool contactDetected = false;

void setup() {
  Serial.begin(9600);

  pinMode(LED_EXTERNAL, OUTPUT);
  pinMode(PHOTOCELL_MODULE, INPUT);
  pinMode(PASSIVE_BUZZER_MODULE, OUTPUT);
  pinMode(LASER_EMIT_MODULE, OUTPUT);

  // Laser is always on
  digitalWrite(LASER_EMIT_MODULE, HIGH);
}

void loop() {

  int currentPhotocellSignalValue = analogRead(PHOTOCELL_MODULE);
  if (currentPhotocellSignalValue < LASER_CONTACT_THRESHOLD) {
    contactDetected = true;
  }

  int buzzerFrequencyHertz = random(MIN_FREQUENCY_HERTZ, MAX_FREQUENCY_HERTZ);
  if (contactDetected) {
    analogWrite(LED_EXTERNAL, LED_EXTERNAL_ON);
    tone(PASSIVE_BUZZER_MODULE, buzzerFrequencyHertz);
    delay(200);
  } else {
    analogWrite(LED_EXTERNAL, LED_EXTERNAL_OFF);
    noTone(PASSIVE_BUZZER_MODULE);

  }

  contactDetected = false;
  delay(25);

}