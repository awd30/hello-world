#ifndef BOPITPRO_H
#define BOPITPRO_H

#include <Arduino.h>
#include <button.h>
#include <touchsensor.h>
#include <slide.h>
#include <speaker.h>
#include <lcdscreen.h>

class BopItPro {
    public:
        BopItPro();

        // I/O
        LCDScreen lcd;
        Speaker speaker;
        Button blue, red, yellow, green;
        TouchSensor right, left, other;
        Slide slideP;

        // Store high score
        int highScore;
        int getHighScore();
        void setHighScore(int);

        // Class functions
        Button getButton(int);
        void boot();
        void preGame();
        void newGame(bool);
};

#endif