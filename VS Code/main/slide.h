#ifndef SLIDE_H
#define SLIDE_H

#include <Arduino.h>
#include "playerinput.h"

class Slide : public PlayerInput {
    public:
        Slide(int n = 0);
        
};

#endif