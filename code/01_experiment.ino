// Experiment 1: Laser beam detection by photocell activates LED
// Description: LED turns on when photocell detects laser beam contact 
// Modules Used: Photocell module, Laser module

// Assign component groupings to Teensy 4.0 pins
const int ledPin = 23;
const int photocellModulePin = 22;
const int laserModulePin = 0;

// Fixed values
const int ledPinOff = 0;
const int ledPinOn = 100;
const int laserContactThreshold = 45;

bool contactDetected = false;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(photocellModulePin, INPUT);

  pinMode(laserModulePin, OUTPUT);
  // Laser is always on
  digitalWrite(laserModulePin, HIGH);
}

void loop() {
  int currentPhotocellSignalValue = analogRead(photocellModulePin);
  Serial.println(currentPhotocellSignalValue);
  if (currentPhotocellSignalValue < laserContactThreshold) {
    contactDetected = true;
  }
  if (contactDetected) {
    analogWrite(ledPin, ledPinOn);
  } else {
    analogWrite(ledPin, ledPinOff);
  }
  contactDetected = false;
  delay(25);
}
