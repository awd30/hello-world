#include <playerinput.h>

PlayerInput::PlayerInput(int n) {
    state = 0;
    pin = n;

    // setup as input
    pinMode(pin, INPUT);
}