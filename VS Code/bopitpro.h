#ifndef BOPITPRO_H
#define BOPITPRO_H

#include <button.h>
#include <touchsensor.h>

class BopItPro {
    public:
        BopItPro();
        ~BopItPro();

        Button blue, red, yellow, green;
        TouchSensor right, left, other;
}

#endif