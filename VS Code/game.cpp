#include <game.h>
#include <stdio.h>
#include <stdlib.h>

// Create new Game instance with bop-it-pro specifics
Game::Game(bool n) {
    level = n;

    // level = 0 --> easy mode
    // level = 1 --> hard mode
    if (level == false) {
        timer = 700;
    } else {
        timer = 300;
    }
}

