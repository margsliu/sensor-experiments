// Experiment #6: Ultrasonic sensor module
// Description: Ultrasonic sensor detects proximity and Active buzzer beeps more rapidly the closer you get. Distance brackets: 0-5cm, 5-15cm, 15-20cm
// Modules Used: Ultrasonic sensor module
// Libraries Used: 
// Comments: 
/* Reference I found useful for the ultrasonic sensor module
    https://projecthub.arduino.cc/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-7cabe1
*/
/* Reference I found useful for the LCD screen
    https://docs.arduino.cc/learn/electronics/lcd-displays/
    https://www.youtube.com/watch?v=g_6OJDyUw1w
*/

#include <LiquidCrystal.h>

// Ultrasonic sensor module
#define ULTRASONIC_SENSOR_MODULE_TRIG 23
#define ULTRASONIC_SENSOR_MODULE_ECHO 22
float ultrasonic_sensor_module_duration; // length of sound wave
float ultrasonic_sensor_module_distance; // calculated distance from object
const float speed_of_sound_in_cm_per_microsecond = 0.0343;
// Active buzzer module
#define ACTIVE_BUZZER_MODULE 6

// LCD
#define LCD_RS_REGISTER_SELECT_PIN 0
#define LCD_E_ENABLE_PIN 1 // 
#define LCD_L4_PIN 2
#define LCD_L5_PIN 3
#define LCD_L6_PIN 4
#define LCD_L7_PIN 5
LiquidCrystal lcd(LCD_RS_REGISTER_SELECT_PIN, LCD_E_ENABLE_PIN, LCD_L4_PIN, LCD_L5_PIN, LCD_L6_PIN, LCD_L7_PIN);

void beepFrequencyMilliseconds(int buzzer_module, int milliseconds) {
  digitalWrite(buzzer_module, HIGH);
  delay(milliseconds);
  digitalWrite(buzzer_module, LOW);
  delay(milliseconds);
  return;
}


void setup() {
  pinMode(ULTRASONIC_SENSOR_MODULE_TRIG, OUTPUT);  
	pinMode(ULTRASONIC_SENSOR_MODULE_ECHO, INPUT); 

  pinMode(ACTIVE_BUZZER_MODULE, OUTPUT);

  // Set up LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Proximity:");

  Serial.begin(9600); // Leaving this here in case I need it later for analog sensors
}

void loop() {

  /* SENSOR MODULE */
  digitalWrite(ULTRASONIC_SENSOR_MODULE_TRIG, LOW);
	delayMicroseconds(2);
	digitalWrite(ULTRASONIC_SENSOR_MODULE_TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(ULTRASONIC_SENSOR_MODULE_TRIG, LOW);
  ultrasonic_sensor_module_duration = pulseIn(ULTRASONIC_SENSOR_MODULE_ECHO, HIGH);
  /* 
   * Explanation of calculation for ultrasonic_sensor_module_distance:
   * Speed = Distance / Time. 
   * Speed of sound is 340 meters/second or 0.0343 c/μS. 
   * Divide by 2 to account for sound waves travelling out and back.
  */
  ultrasonic_sensor_module_distance = (ultrasonic_sensor_module_duration * speed_of_sound_in_cm_per_microsecond)/2; 
  Serial.println(ultrasonic_sensor_module_distance);

  /* ACTIVE BUZZER */
  if (ultrasonic_sensor_module_distance <= 5) {
    beepFrequencyMilliseconds(ACTIVE_BUZZER_MODULE, 50);
  } else if (ultrasonic_sensor_module_distance <= 15 ) {
    beepFrequencyMilliseconds(ACTIVE_BUZZER_MODULE, 200);
  } else if (ultrasonic_sensor_module_distance <= 20) {
    beepFrequencyMilliseconds(ACTIVE_BUZZER_MODULE, 400);
  } else {
    // quiet
  }

  /* LCD DISPLAY */
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print(ultrasonic_sensor_module_distance);
  lcd.print(" cm");
  delay(5);
}