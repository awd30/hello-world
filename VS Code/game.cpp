#include <game.h>
#include <bopitpro.h>
#include <stdio.h>
#include <stdlib.h>

// Create new Game instance with bop-it-pro specifics
Game::Game(bool n) {
    level = n;
    currentScore = 0;
    finalScore = 0;

    // level = false --> easy mode
    // level = true --> hard mode
    if (level == false) {
        timer = 700;
    } else {
        timer = 300;
    }
}

void Game::start() {
    
}

void Game::gameOver(BopItPro bop) {
    // play 'incorrect' sound
    bop.speaker.gameOver();

    // display 'game over' message, communicate final score
    finalScore = currentScore;
    bop.lcd.gameOver(finalScore);
    bop.setHighScore(finalScore);
}

