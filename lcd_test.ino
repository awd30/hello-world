#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // initialize the lcd 
  lcd.init();
  // print message to lcd
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Welcome!");
  lcd.setCursor(2,1);
  lcd.print("Press anywhere to continue!");
}

void loop() {}
