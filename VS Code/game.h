#ifndef GAME_H
#define GAME_H

#define SEQUENCE_SIZE 100

#include <string>
#include <stdlib.h>
using namespace std;

class Game {
    public:
        Game(bool);
        ~Game();

        bool level;
        int timer;
        unsigned long timeOfPrompt, timeElapsed;
        long action;

        void gameOver();
        void ();
};

#endif