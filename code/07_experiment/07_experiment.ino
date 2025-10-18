// Experiment #7: Piezoelectric sensor
// Description: Test piezo functionality, sending MIDI CC messages based on input to Max/MSP
// Modules Used: Piezoelectric sensor module

#define PIEZOELECTRIC_MODULE 22


void setup() {
  pinMode(PIEZOELECTRIC_MODULE, INPUT);
  Serial.begin(9600);
}

void loop() {
  int piezoelectricValue = analogRead(PIEZOELECTRIC_MODULE);
  int piezoelectricValueMIDI = map(piezoelectricValue, 0, 1024, 0, 127); 
  Serial.println(piezoelectricValue);
  usbMIDI.sendControlChange(7, piezoelectricValue, 1);
  delay(5);  
}
