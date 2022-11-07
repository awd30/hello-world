#include <LiquidCrystal_I2C.h>
#include <lcdscreen.h>

LCDScreen::LCDScreen() {
    LiquidCrystal_I2C lcd(0x27,16,2);
    lcd.begin(16, 2);
    lcd.backlight();
}

void LCDScreen::welcome() {
    lcd.setCursor(0, 0);         // move cursor to   (0, 0)
    lcd.print("Welcome to");     // print message at (0, 0)
    lcd.setCursor(5, 1);         // move cursor to   (5, 1)
    lcd.print("BOP-IT PRO!");    // print message at (5, 1)
}

void LCDScreen::start() {
    lcd.setCursor(0, 0);
    lcd.print("Press & hold any");
    lcd.setCursor(0, 1);
    lcd.print("button to start");
    delay(50);
}

void LCDScreen::difficultyLevel() {
    lcdDisplay();
    lcd.print("DIFFICULTY ");
    lcd.setCursor(11, 1);
    lcd.print("LEVEL");
    delay(100);
    lcdDisplay();
    lcd.print("GREEN FOR EASY");
    lcd.setCursor(0, 1);
    lcd.print("RED FOR HARD");
    delay(200);
}

void LCDScreen::difficultyLevel(string level) {
    lcdDisplay();
    lcd.print("  YOU SELECTED  ");
    lcd.setCursor(0, 1);
    
    if (level.tolower() == "hard") {
        lcd.print("   HARD LEVEL   ");
    } else {
        lcd.print("   EASY LEVEL   ");
    }

    delay(100);
}

void LCDScreen::gameOver(char score[10]) {
    lcdDisplay();
    lcd.print("GAME OVER!");
    delay(100);
    lcdDisplay();
    lcd.print("SCORE: ");
    lcd.setCursor(7, 0);                    
    lcd.print(scoreString);
    delay(500);
}

void LCDScreen::press(String color) {
    char color_buf [10];
    color.toCharArray(color_buf);
    lcdDisplay();
    lcd.print("PRESS ");
    lcd.setCursor(6, 0);                   
    lcd.print(color_buf);
}