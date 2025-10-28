#include <CapacitiveSensor.h> // https://github.com/PaulStoffregen/CapacitiveSensor

CapacitiveSensor cSensor = CapacitiveSensor(11,12);
const int sensitivity = 30;

void setup()                    
{
   cSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long sensorVal =  cSensor.capacitiveSensor(sensitivity);

    sensorVal = constrain(sensorVal, 8000, 22000);
    sensorVal = map(sensorVal, 8000, 22000, 0, 127);
    usbMIDI.sendControlChange(1, sensorVal, 1);

    Serial.println(millis() - start);
    Serial.println(sensorVal);                  // print cSensor output 1

    delay(10);                             // arbitrary delay to limit data to serial port 
}
