#include <button.h>

Button::Button(int n, String c) {
    state = 0;
    num = n;
    color = c;

    // setup as input
    pinMode(num, INPUT);
}

