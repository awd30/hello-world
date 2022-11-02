#ifndef LCDSCREEN_H
#define LCDSCREEN_H

class LCDScreen {
    private:
        LiquidCrystal_I2C lcd(0x27,16,2);

    public:
        LCDScreen();
        ~LCDScreen();

        void welcome();
        
};

#endif