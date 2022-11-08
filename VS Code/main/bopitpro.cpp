#include "bopitpro.h"
#include "game.h"

BopItPro::BopItPro() {
    // Create instance of LCD screen
    lcd = LCDScreen();

    // Create incstance of speaker
    speaker = Speaker();
    
    // Create instances of all 4 buttons
    blue = Button(2);
    red = Button(3);
    yellow = Button(4);
    green = Button(5);

    // Create instances of all 3 touch sensors
    right = TouchSensor(6);
    left = TouchSensor(7);
    other = TouchSensor(9);

    // Create instance of slide petentiometer
    slideP = Slide(11);
}

void BopItPro::boot() {
    Serial.begin(9600);
    lcd.welcome();
}

void BopItPro::preGame() {
    lcd.start();

    // Poll for any button press
    if(blue.getState() == HIGH || red.getState() == HIGH || yellow.getState() == HIGH || green.getState() == HIGH) {
        // Display difficulty level
        lcd.difficultyLevel();

        // Read red/green button press, assign corresponding difficulty level
        // level = false --> easy
        // level = true --> hard
        bool level = false;
        if (red.getState() == HIGH) {
            level = false;
        } else if (green.getState() == HIGH) {
            level = true;
        }

        // Display selection, create new game with level selection
        lcd.levelSelection(level);
        newGame(level);
    }
}

void BopItPro::newGame(bool level) {
    Game game = Game(level);
    game.start(*this);

    // start program over
    preGame();
}

int BopItPro::getHighScore() {
    return highScore;
}

void BopItPro::setHighScore(int score) {
    if (score > highScore) {
        highScore = score;
    }
}

Button BopItPro::getButton(int n) {
    if (n == 2) { return blue; }
    else if (n == 3) { return red; }
    else if (n == 4) { return yellow; }
    else if (n == 5) { return green; }
}