#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

#include <Arduino.h>

class TouchSensor : public PlayerInput {
    public:
        TouchSensor(int n = 0);
};

#endif