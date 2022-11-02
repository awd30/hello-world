#include <lcdscreen.h>
#include <..\Arduino\libraries\LiquidCrystal_I2C\LiquidCrystal_I2C.h>

LCDScreen::LCDScreen() {
    LiquidCrystal_I2C lcd(0x27,16,2);
}

void LCDScreen::welcome() {
    lcd.setCursor(0, 0);         // move cursor to   (0, 0)
    lcd.print("Welcome to");     // print message at (0, 0)
    lcd.setCursor(5, 1);         // move cursor to   (5, 1)
    lcd.print("BOP-IT PRO!");    // print message at (5, 1)
}