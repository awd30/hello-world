#ifndef BOPITPRO_H
#define BOPITPRO_H

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

        // Store final game scores

        void boot();
        void preGame();
        void newGame(bool);
        
        void readBtnStates();
};

#endif