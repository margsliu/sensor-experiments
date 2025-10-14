// Experiment #5: LCD module Hello World w/ system runtime seconds counter
// Description: LCD displays hello world text and updates a seconds counter.
// Comments: The majority of this code isn't mine (I loaded in hello world code from arduino.cc docs), I just copied 
//           and pasted from the arduino.cc example and updated my pin references. The goal of this exercise was to 
//           get the LCD wired up and displaying text, and being able to adjust contrast with a potentiometer.
// Modules Used: LCD 1602
// Libraries Used: LiquidCrystal
/* Reference I found useful
    https://docs.arduino.cc/learn/electronics/lcd-displays/
    https://www.youtube.com/watch?v=g_6OJDyUw1w
*/

// include the library code:
#include <LiquidCrystal.h>

/* RS Pin controls where in the LCD's memory you're writing data to. 
  You can select either the data register, which holds what goes on 
  the screen, or an instruction register, which is where the LCD's 
  controller looks for instructions on what to do next.
*/
#define LCD_RS_REGISTER_SELECT_PIN 0
/* E Pin enables writing to the registers */
#define LCD_E_ENABLE_PIN 1 // 
#define LCD_L4_PIN 2
#define LCD_L5_PIN 3
#define LCD_L6_PIN 4
#define LCD_L7_PIN 5

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(LCD_RS_REGISTER_SELECT_PIN, LCD_E_ENABLE_PIN, LCD_L4_PIN, LCD_L5_PIN, LCD_L6_PIN, LCD_L7_PIN);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}