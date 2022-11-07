#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

class TouchSensor {
    public:
        TouchSensor(int);
        ~TouchSensor();

        int state, pin;
};

#endif