#ifndef GAME_H
#define GAME_H

#define SEQUENCE_SIZE 100

class Game {
    public:
        Game(bool);

        bool level;
        int timer, currentScore, finalScore;
        unsigned long timeOfPrompt, timeElapsed;
        long action;

        void start();
        void gameOver(BopItPro);
        void correctTurn();
};

#endif