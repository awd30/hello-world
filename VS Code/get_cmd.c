#ifndef SEQUENCE_H
#define SEQUENCE_H

struct Sequence {
    // protected:
    int totalTurns;
    int * seqTurns;

    // private:
    char * seqDisplay;
};

extern const struct SequenceClass {
    struct Sequence (*new)(int totalTurns, int * seqTurns);
} Sequence;

#endif

// Function to get bop-it sequence
void init_seq() {
    // Need to include:
    //      srand(time(0))
    // in the main code (driver code) 
    int upper = 3; // Number of different functions
    int lower = 1;
    int totalTurns = 100; // Total turns before game over (if user didn't fail)
    int seq[totalTurns]; // Turn (correct button/function) sequence
    
    // Generate random turn sequence
    for (int i = 0; i < totalTurns; i++) {
        int n = (rand() % (upper - lower + 1)) + lower;
        seq[i] = n;
    }
}

int 

int getDisplayText(cmd) {

}