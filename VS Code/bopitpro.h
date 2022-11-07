#ifndef BOPITPRO_H
#define BOPITPRO_H

#include <button.h>
#include <touchsensor.h>
#include <slide.h>

class BopItPro {
    public:
        BopItPro();

        Button blue, red, yellow, green;
        TouchSensor right, left, other;
        Slide slideP;
};

#endif