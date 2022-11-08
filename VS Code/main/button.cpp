#include "button.h"

Button::Button(int n) : PlayerInput(n) {
    if (n == 2) { color = "BLUE"; }
    else if (n == 3) { color = "RED"; }
    else if (n == 4) { color = "YELLOW"; }
    else if (n == 5) { color = "GREEN"; }
}

String Button::getColor() {
    return color;
}
