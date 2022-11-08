#include "slide.h"

Slide::Slide(int n) : PlayerInput(n) {}

int Slide::getState() {
    state = analogRead(pin);
    return state;
}