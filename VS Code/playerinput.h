#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

#include <Arduino.h>

class PlayerInput {
    public:
        PlayerInput(int);

        int state, pin;

        int getState();
        int getPin();
};

#endif