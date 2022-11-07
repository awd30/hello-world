#include <game.h>
#include <stdio.h>
#include <stdlib.h>

// Create new Game instance with bop-it-pro specifics
Game::Game(bool n) {
    level = n;
    score = 0;
    finalScore = 0;

    // level = false --> easy mode
    // level = true --> hard mode
    if (level == false) {
        timer = 700;
    } else {
        timer = 300;
    }
}

void Game::gameOver() {

}

