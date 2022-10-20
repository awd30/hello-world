#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  // initialize the lcd
  lcd.init(); 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Welcome!");
  lcd.setCursor(2,1);
  lcd.print("Press anywhere to begin");
  lcd.setCursor(0,2);
  lcd.print("!!!!");
  lcd.setCursor(2,3);
  lcd.print(":)");
}

void loop() {}
