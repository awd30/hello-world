#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <playerinput.h>

class Button : public PlayerInput {
    public:
        Button(int n = 0);
        
        String color;
        String getColor();
};

#endif