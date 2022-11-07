#include <button.h>

Button::Button(int n) {
    state = 0;
    num = n;

    // setup as input
    pinMode(num, INPUT);
}

