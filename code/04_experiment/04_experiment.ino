// Experiment #4: Photo-interruptor Module + LCD 1602 Module
// Description: Current value from photo-interruptor module gets displayed on LCD screen.
// Modules Used: Photo-interruptor Module, LCD 1602
// Libraries Used: LiquidCrystal
// Comments: 
/* Reference I found useful for the LCD screen
    https://docs.arduino.cc/learn/electronics/lcd-displays/
    https://www.youtube.com/watch?v=g_6OJDyUw1w
*/

#include <LiquidCrystal.h>

// Photo interruptor module
#define PHOTO_INTERRUPTOR_MODULE 23
int sensorValue;

// LCD
#define LCD_RS_REGISTER_SELECT_PIN 0
#define LCD_E_ENABLE_PIN 1 // 
#define LCD_L4_PIN 2
#define LCD_L5_PIN 3
#define LCD_L6_PIN 4
#define LCD_L7_PIN 5
LiquidCrystal lcd(LCD_RS_REGISTER_SELECT_PIN, LCD_E_ENABLE_PIN, LCD_L4_PIN, LCD_L5_PIN, LCD_L6_PIN, LCD_L7_PIN);


void setup() {
  Serial.begin(9600); // Leaving this here in case I need it later for analog sensors
  // Set up LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Sensor Value:");
}

void loop() {
  
  sensorValue = analogRead(PHOTO_INTERRUPTOR_MODULE);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);
  delay(500);
}