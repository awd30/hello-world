#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCDScreen {
    public:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);
        LCDScreen();

        void welcome();
        void start();
        void difficultyLevel();
        void levelSelection(bool);
        void gameOver(int);
        void press(String);
        void lcdDisplay();
};

#endif