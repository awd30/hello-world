#ifndef GAME_H
#define GAME_H

#define SEQUENCE_SIZE 100
#include <Arduino.h>

class Game {
    public:
        Game(bool);

        bool level;
        const String colors[4] = { "RED", "GREEN", "BLUE", "YELLOW" };
        int timer, currentScore, finalScore, playing;
        unsigned long timeOfPrompt, timeElapsed;
        long action;

        void start(BopItPro);
        void turn(long, BopItPro);
        void correctAction(BopItPro);
        void gameOver(BopItPro);
};

#endif