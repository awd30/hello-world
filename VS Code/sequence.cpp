#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

Sequence::Sequence() {
    this->initSeq();
    this->initDisplay();
}

// Function to get bop-it sequence turn numbers
void Sequence::initSeq() {
    // Need to include:
    //      srand(time(0))
    // in the main code (driver code)

    int upper = 3; // Number of different functions
    int lower = 1;
    
    // Generate random turn sequence
    for (int i = 0; i < this->getTotTurns(); i++) {
        int n = (rand() % (upper - lower + 1)) + lower;
        this->setTurn(i, n);
    }
}

// Function to set display values
void Sequence::initDisplay() {
    this->setSeq(0, "Begin!");
    this->setSeq(1, "Pull it!");
    this->setSeq(2, "Push the left button!");
    this->setSeq(3, "Push the right button!");
}