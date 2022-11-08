#include "slidepot.h"

SlidePot::SlidePot(int n) : PlayerInput(n) {}

void SlidePot::setOldState() {
    oldState = analogRead(pin);
}

int SlidePot::getState() {
    state = analogRead(pin);
    return state;
}

int SlidePot::