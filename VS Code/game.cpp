#include <game.h>
#include <bopitpro.h>
#include <stdio.h>
#include <stdlib.h>

// Create new Game instance with bop-it-pro specifics
Game::Game(bool n) {
    level = n;
    playing, currentScore, finalScore = 0;

    // level = false --> easy mode
    // level = true --> hard mode
    if (level == false) {
        timer = 700;
    } else {
        timer = 300;
    }
}

void Game::start(BopItPro bop) {
    playing = 1;
    
    // game runs until user has failed, playing set to 0
    while (playing != 0) {
        // generate random action
        action = random(2, 5);
        turn(action, bop);
    }
}

void Game::turn(long action, BopItPro bop) {    
    // print turn directions
    bop.lcd.press(colors[action - 2]);

    // poll for completed action while timer has not run out
    timeOfPrompt = millis();
    timeElapsed = millis() - timeOfPrompt;
    while (timeElapsed < timer) {
        // read switch states, check for correct action
        for (int i = 2; i < 6; i++) {
            if (bop.getButton(i).getState() == HIGH) {
                // correct button pushed
                if (action == i) { 
                    correctAction(bop);
                } 
                // incorrect button pushed
                else {
                    gameOver(bop);
                }
            }
        }
    }
}

void Game::correctAction(BopItPro bop) {
    // add to score
    currentScore++;

    // play 'correct' sound
    bop.speaker.correctAction();
}

void Game::gameOver(BopItPro bop) {
    playing = 0;
    
    // play 'incorrect' sound
    bop.speaker.gameOver();

    // display 'game over' message, communicate final score
    finalScore = currentScore;
    bop.lcd.gameOver(finalScore);
    bop.setHighScore(finalScore);
}

