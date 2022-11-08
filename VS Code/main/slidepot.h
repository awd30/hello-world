#ifndef SLIDEPOT_H
#define SILDEPOT_H

#include <Arduino.h>
#include "playerinput.h"

class SlidePot : public PlayerInput {
    public:
        SlidePot(int n = 0);

        int oldState = 0;
        int getState();      
};

#endif