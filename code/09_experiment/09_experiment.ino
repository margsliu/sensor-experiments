// Momentary button switch activates MIDI note send.
int pushButton = 11;
bool noteSent = false;
bool noteOffSent = false;

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(pushButton, INPUT);
}

void loop() {
  int pushButtonState = digitalRead(pushButton);

  if (pushButtonState == 0 && noteSent == false) {
    usbMIDI.sendNoteOn(60, 127, 1);
    noteSent = true;
    noteOffSent = false;
    Serial.println("Send a note");
  }

  if (pushButtonState == 1 && noteOffSent == false) {
    usbMIDI.sendNoteOff(6, 0, 1);
    noteOffSent = true;
    noteSent = false;
    Serial.println("Send note off");
  }

  // Serial.println(pushButtonState);
  delay(5);
}
