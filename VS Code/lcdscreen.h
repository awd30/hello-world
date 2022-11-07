#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#include <string>

class LCDScreen {
    private:
        LiquidCrystal_I2C lcd(0x27,16,2);

    public:
        LCDScreen();

        void welcome();
        void start();
        void difficultyLevel();
        void levelSelection(bool);
        void gameOver(int);
        void press(String);
};

#endif