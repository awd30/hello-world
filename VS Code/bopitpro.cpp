#include <bopitpro.h>

BopItPro::BopItPro() {
    // Create instances of all 4 buttons
    blue = Button(2);
    red = Button(3);
    yellow = Button(4);
    green = Button(5);

    // Create instances of all 3 touch sensors
    right = TouchSensor(6);
    left = TouchSensor(7);
    other = TouchSensor(9);
}