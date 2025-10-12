// Experiment 2: Laser beam detection by photocell activates LED and buzzer
// Description: When photocell detects laser beam contact, LED turns on and passive buzzer sounds at a random frequency (Hz).
// Modules Used: Photocell module, Laser module, Passive buzzer module

// Assign component groupings to Teensy 4.0 pins
const int ledPin = 23;
const int photocellModule = 22;
const int laserModule = 0;
const int passiveBuzzerModule = 1;

// Set LED on/off brightness
const int ledPinOff = 0;
const int ledPinOn = 100;
// Set photocell laser detection threshold (maximum brightness begins at 0)
const int laserContactThreshold = 45;
// Set frequency range of buzzer tone
const int minFrequencyHertz = 100;
const int maxFrequencyHertz = 2000;

bool contactDetected = false;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(photocellModule, INPUT);
  pinMode(passiveBuzzerModule, OUTPUT);

  pinMode(laserModule, OUTPUT);
  // Laser is always on
  digitalWrite(laserModule, HIGH);
}

void loop() {

  int currentPhotocellSignalValue = analogRead(photocellModule);
  if (currentPhotocellSignalValue < laserContactThreshold) {
    contactDetected = true;
  }

  int buzzerFrequencyHertz = random(minFrequencyHertz, maxFrequencyHertz);
  if (contactDetected) {
    analogWrite(ledPin, ledPinOn);
    tone(passiveBuzzerModule, buzzerFrequencyHertz);
    delay(200);
  } else {
    analogWrite(ledPin, ledPinOff);
    noTone(passiveBuzzerModule);

  }

  contactDetected = false;
  delay(25);

}