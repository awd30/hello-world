#ifndef SPEAKER_H
#define SPEAKER_H

#include <Arduino.h>

class Speaker {
    public:
        Speaker();

        void gameOver();
        void correctAction();
};

#endif