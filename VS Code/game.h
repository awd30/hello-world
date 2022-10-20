#ifndef GAME_H
#define GAME_H

#define SEQUENCE_SIZE 100

#include <string>
#include <stdlib.h>
using namespace std;

class Game {
    private:
        string * seqDisplay;
        int seqTurns[SEQUENCE_SIZE];
        int totalTurns = SEQUENCE_SIZE;
        int turnCount = 0;

        void setTurn(int x, int y) { seqTurns[x] = y; }
        void setSeq(int x, string y) { seqDisplay[x] = y; }

        void initSeq();
        void initDisplay();
        void startGame();
        void takeTurn();
        void correctTurn();
        void wrongTurn();

    public:
        Game();
        ~Game();

        void setTotTurns(int n) { totalTurns = n; }

        int getTurn(int n) { return seqTurns[n]; }
        int getTotTurns() { return totalTurns; }
        string getDisplayText(int n) { return seqDisplay[n]; }
};

#endif