#include "playerinput.h"

PlayerInput::PlayerInput(int n) {
    state = 0;
    pin = n;

    // setup as input
    pinMode(pin, INPUT);
}

int PlayerInput::getPin() {
    return pin;
}

int PlayerInput::getState() {
    state = digitalRead(pin);
    return state;
}