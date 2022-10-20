#ifndef SEQUENCE_H
#define SEQUENCE_H

#define SEQUENCE_SIZE 100

#include <string>
#include <stdlib.h>
using namespace std;

class Sequence {
    protected:
        int totalTurns = SEQUENCE_SIZE;

    private:
        string * seqDisplay;
        int seqTurns[SEQUENCE_SIZE];

        void setTurn(int x, int y) { seqTurns[x] = y; }
        void setSeq(int x, string y) { seqDisplay[x] = y; }

        void initSeq();
        void initDisplay();

    public:
        Sequence();
        ~Sequence();

        void setTotTurns(int n) { totalTurns = n; }

        int getTurn(int n) { return seqTurns[n]; }
        int getTotTurns() { return totalTurns; }
        string getDisplayText(int n) { return seqDisplay[n]; }

};

#endif