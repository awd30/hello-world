<<<<<<< HEAD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//Buttons define
#define btnBlue 2
#define btnRed 3
#define btnYellow 4
#define btnGreen 5

#define slideP A1

int blueState = 0;
int redState = 0;
int yellowState = 0;
int greenState = 0;

//Touch Sensor
#define TSR 6
#define TSL 7
#define TSO 9

//Timer
#define hardMode 300
#define easyMode 700
unsigned long timeOfPrompt, timeElapsed;
long action;

// variable to control game loop
int playing1 = 0;
int actionCompleted = 0;
int score = 0;
int finalScore;
  
//setup
void setup() 
{
  pinMode(btnBlue, INPUT);
  pinMode(btnRed, INPUT);
  pinMode(btnYellow, INPUT);
  pinMode(btnGreen, INPUT);
  pinMode(slideP, INPUT);
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();
  welcome();
  delay(300);
}

void loop() 
{
  start();
}

//Welcome message
void welcome()
{
  lcd.setCursor(0, 0);         // move cursor to (0, 0)
  lcd.print("Welcome to");     // print message at (0, 0)
  lcd.setCursor(5, 1);         // move cursor to (5, 1)
  lcd.print("BOP-IT PRO!");    // print message at (5, 1)
}

//Start Message
void start()
{
  // lcd.setCursor(0, 0);
  // lcd.print("Press & hold any");
  // lcd.setCursor(0, 1);
  // lcd.print("button to start");
  // delay(50);

  lcd.clear();
  int state = analogRead(slideP);
  bool stop = 0;
  int diff, currentState;
  lcd.setCursor(0, 0);
  lcd.print("Slide: ");
  lcd.print(state);

  while (stop == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Slide: ");
    int currentState = analogRead(slideP);
    lcd.print(currentState);

    int diff = abs(currentState - state);
    lcd.setCursor(0, 1);
    lcd.print("diff: ");
    lcd.print(diff);  
    
    if (diff >= 500) {
      stop = 1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("complete");
      delay(300);
    }
  }

}

// Update button state global variables with current values
void readBtnStates()
{
  blueState = digitalRead(btnBlue);
  redState = digitalRead(btnRed);
  yellowState = digitalRead(btnYellow);
  greenState = digitalRead(btnGreen);
}

//Button Function
void pressAnyButton()
{
  readBtnStates();
      //blue                    red                   yellow            green
  if(blueState == HIGH || redState == HIGH || yellowState == HIGH || greenState == HIGH)
  {
    gameMode(); //Displays difficulty level
    if(redState == HIGH)
    {
      hardGameStart();
      delay(200);      
    }
    else if(greenState == HIGH)
    {
      easyGameStart();
      delay(200);   
    }
  }   
  else
  {
    start();
    delay(50);
    lcd.noDisplay();
    delay(50);
    lcd.display();
  }
}

void gameMode()
{
  redState = digitalRead(btnRed);
  greenState = digitalRead(btnGreen);
    lcdDisplay();
    lcd.print("DIFFICULTY ");
    lcd.setCursor(11, 1);
    lcd.print("LEVEL");
    delay(100);
    lcdDisplay();
    lcd.print("GREEN FOR EASY");
    lcd.setCursor(0, 1);
    lcd.print("RED FOR HARD");
    delay(200);
}    

//Game mode hard, timer = 3 secs
void hardGameStart()
{
    lcdDisplay();
    lcd.print("  YOU SELECTED  ");
    lcd.setCursor(0, 1);
    lcd.print("   HARD LEVEL   ");
    delay(100);
    //keepPlayingHard();
}
void easyGameStart()
{
    lcdDisplay();
    lcd.print("  YOU SELECTED  ");
    lcd.setCursor(0, 1);
    lcd.print("   EASY LEVEL   ");
    delay(100);
    keepPlayingEasy();
}
void lcdDisplay()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}
void gameOver()
{
  playing1 = 0;
  score = 0;
  
  tone(6, 100, 100);
  delay(100);
  noTone(6);
  finalScore = score;
  char scoreString[10];
  sprintf(scoreString,"%d",finalScore);
  lcdDisplay();
  lcd.print("GAME OVER!");
  delay(100);
  lcdDisplay();
  lcd.print("SCORE: ");
  lcd.setCursor(7, 0);                    
  lcd.print(scoreString);
  delay(500);
  start();
}
void keepPlayingEasy()
{
  playing1 = 1;
  //while loop to keep running game until user has failed and "playing1" is set to zero
  while (playing1 != 0) 
  {   
    //pick an action to assign the user via a random number generator – upper bound is exclusive
    action = random(1, 4);
    actionCompleted = 0;
    if (action == 1)
    {
      lcdDisplay();
      lcd.print("PRESS RED");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 1 = Press Red Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        //read switch for comparing to check if action was completed
        //if the switch state changed, then the user completed action
        if (redState == HIGH)
        {
          actionCompleted = 1;
          score = score +1;
        }
        else if(greenState == HIGH || blueState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
        tone(6, 5000, 50); //tone(pin, freq, duration)
        delay(50);
        noTone(6);
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }

    }
    //Action 2
    else if (action == 2)
    {
      lcdDisplay();
      lcd.print("PRESS GREEN");    
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 1 = Press Red Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        //read switch for comparing to check if action was completed
        //if the switch state changed, then the user completed action
        if (greenState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || blueState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
        tone(6, 5000, 50); //tone(pin, freq, duration)
        delay(50);
        noTone(6);
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }
    }

    //Action 3
    else if (action == 3)
    {
      lcdDisplay();
      lcd.print("PRESS BLUE");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 3 = Press BLUE Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        //read switch for comparing to check if action was completed
        //if the switch state changed, then the user completed action
        if (blueState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
        tone(6, 5000, 50); //tone(pin, freq, duration)
        delay(50);
        noTone(6);
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }
    }

    //Action 4
    else if (action == 4)
    {
      lcdDisplay();
      lcd.print("PRESS YELLOW");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 3 = Press BLUE Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        //read switch for comparing to check if action was completed
        //if the switch state changed, then the user completed action
        if (yellowState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
        tone(6, 5000, 50); //tone(pin, freq, duration)
        delay(50);
        noTone(6);
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }
    }
  }
}//end this function
/*
void keepPlayingHard()
{
  playing1 = 1;
  //while loop to keep running game until user has failed and "playing1" is set to zero
  while (playing1 != 0) 
  {   
    //pick an action to assign the user via a random number generator – upper bound is exclusive
    action = random(1, 4);
    actionCompleted = 0;
    if (action == 1)
    {
      lcdDisplay();
      lcd.print("PRESS RED");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 1 = Press Red Button  
      while (timeElapsed < hardMode && actionCompleted == 0)
      {
        //read switch for comparing to check if action was completed
        readBtnStates();
        //if the switch state changed, then the user completed action
        if (redState == HIGH)
        {
          actionCompleted = 1;
          score = score +1;
        }
        else if(greenState == HIGH || blueState == HIGH || yellowState == HIGH)
        {
          gameOver();
          loop();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
        tone(6, 5000, 50); //tone(pin, freq, duration)
        delay(50);
        noTone(6);
      }
      else if(timeOfPrompt == 300 && actionCompleted == 0)
      {
        gameOver();
        loop();
      }

    }
  }
}//end this function
*/
=======
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <SD.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//Buttons define
const int btnBlue = 2;
const int btnRed = 3;
const int btnYellow = 4;
const int btnGreen = 5;

int blueState = 0;
int redState = 0;
int yellowState = 0;
int greenState = 0;

//POT
int potPin = A1;
int potValue = 0;

//Touch Sensor
const int TSR = 7;
const int TSL = 9;
const int TSU = 10;

//TOUCH STATE
int rightTouch = 0;
int leftTouch = 0;
int upTouch = 0;

//Timer
int hardMode = 300;
int easyMode = 700;
unsigned long timeOfPrompt, timeElapsed;
int timer;
long action;

// variable to control game loop
int playing1 = 0;
int actionCompleted = 0;
int score = 0;
int finalScore;
  
//setup
void setup() 
{
  pinMode(btnBlue, INPUT);
  pinMode(btnRed, INPUT);
  pinMode(btnYellow, INPUT);
  pinMode(btnGreen, INPUT);
  pinMode(rightTouch, INPUT);
  pinMode(leftTouch, INPUT);
  pinMode(upTouch, INPUT); //Uptouch
  pinMode(A1, INPUT); //pot
  
  Serial.begin(9600);
  //sd_check();  
  lcd.begin(16, 2);
  lcd.backlight();
  welcome();
  delay(300);
}

void loop() 
{
  pressAnyButton();
}

//Welcome message
void welcome()
{
  lcd.setCursor(0, 0);         // move cursor to (0, 0)
  lcd.print("Welcome to");     // print message at (0, 0)
  lcd.setCursor(5, 1);         // move cursor to (5, 1)
  lcd.print("BOP-IT PRO!");    // print message at (5, 1)
}

//Start Message
void start()
{
  lcd.setCursor(0, 0);
  lcd.print("Press & hold any");
  lcd.setCursor(0, 1);
  lcd.print("button to start");
  delay(50);
}

// Update button state global variables with current values
void readBtnStates()
{
  blueState = digitalRead(btnBlue);
  redState = digitalRead(btnRed);
  yellowState = digitalRead(btnYellow);
  greenState = digitalRead(btnGreen);
  rightTouch = digitalRead(TSR);
  leftTouch = digitalRead(TSL);
  upTouch = digitalRead(TSU);
}
void rightSound()
{
  tone(6, 5000, 20); //tone(pin, freq, duration)
  delay(50);
  noTone(6);
}
void gameOverSound()
{
  tone(6, 100, 100);
  delay(50);
  noTone(6);
}
//Button Function
void pressAnyButton()
{
  readBtnStates();
      //blue                    red                   yellow            green
  if(blueState == HIGH || redState == HIGH || yellowState == HIGH || greenState == HIGH)
  {
    gameMode(); //Displays difficulty level
    if(redState == HIGH)
    {
      hardGameStart();
      delay(200);      
    }
    else if(greenState == HIGH)
    {
      easyGameStart();
      delay(200);   
    }
  }   
  else
  {
    start();
    delay(50);
    lcd.noDisplay();
    delay(50);
    lcd.display();
  }
}

void gameMode()
{
  readBtnStates();
    lcdDisplay();
    lcd.print("DIFFICULTY ");
    lcd.setCursor(11, 1);
    lcd.print("LEVEL");
    delay(100);
    lcdDisplay();
    lcd.print("GREEN FOR EASY");
    lcd.setCursor(0, 1);
    lcd.print("RED FOR HARD");
    delay(200);
}    

//Game mode hard, timer = 3 secs
void hardGameStart()
{
    lcdDisplay();
    lcd.print("  YOU SELECTED  ");
    lcd.setCursor(0, 1);
    lcd.print("   HARD LEVEL   ");
    delay(100);
    keepPlayingHard();
}
void easyGameStart()
{
    lcdDisplay();
    lcd.print("  YOU SELECTED  ");
    lcd.setCursor(0, 1);
    lcd.print("   EASY LEVEL   ");
    delay(100);
    keepPlayingEasy();
}
void lcdDisplay()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}


//POT
void slider()
{
  // read the value from the sensor:
  potValue = analogRead(potPin);
  potValue = potValue * 5 / 1023 ; //its convert digital value back into voltage
  // turn the ledPin on
  
}
void gameOver()
{
  playing1 = 0;
  gameOverSound(); 
  finalScore = score;
  char scoreString[10];
  sprintf(scoreString,"%d",finalScore);
  lcdDisplay();
  lcd.print("GAME OVER!");
  delay(100);
  lcdDisplay();
  lcd.print("SCORE: ");
  lcd.setCursor(7, 0);                    
  lcd.print(scoreString);
  delay(300);
  score = 0;
  start();
}
void keepPlayingEasy()
{
  playing1 = 1;
  //while loop to keep running game until user has failed and "playing1" is set to zero
  while (playing1 != 0) 
  {   
    //pick an action to assign the user via a random number generator – upper bound is exclusive
    action = random(1, 8);
    actionCompleted = 0;
    if (action == 1)
    {
      lcdDisplay();
      lcd.print("PRESS RED");
      timeOfPrompt = millis(); //time displayed
      timeElapsed = millis() - timeOfPrompt;
      //Action 1 = Press Red Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates(); 
        if (redState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(greenState == HIGH || blueState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
      timeElapsed = millis() - timeOfPrompt;
      int time = (timeElapsed - timeOfPrompt)/100;
      lcd.setCursor(0, 1);
      char string[1];
      sprintf(string,"%d",time);
      lcd.print(time);
      }
      if (actionCompleted == 1)
      {
        rightSound();
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }

    }
    //Action 2
    else if (action == 2)
    {
      lcdDisplay();
      lcd.print("PRESS GREEN"); 
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 1 = Press Red Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        if (greenState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || blueState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
      timeElapsed = millis() - timeOfPrompt;
      int time = (timeElapsed - timeOfPrompt)/100;
      lcd.setCursor(0, 1);
      char string[1];
      sprintf(string,"%d",time);
      lcd.print(time);
      }
      if (actionCompleted == 1)
      {
        rightSound();
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }
    }

    //Action 3
    else if (action == 3)
    {
      lcdDisplay();
      lcd.print("PRESS BLUE");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 3 = Press BLUE Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        if (blueState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
      timeElapsed = millis() - timeOfPrompt;
      int time = (timeElapsed - timeOfPrompt)/100;
      lcd.setCursor(0, 1);
      char string[1];
      sprintf(string,"%d",time);
      lcd.print(time);
      }
      if (actionCompleted == 1)
      {
        rightSound();
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }
    }

    //Action 4
    else if (action == 4)
    {
      lcdDisplay();
      lcd.print("PRESS YELLOW");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //easyTimer();
      //Action 3 = Press BLUE Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        if (yellowState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
      timeElapsed = millis() - timeOfPrompt;
      int time = (timeElapsed - timeOfPrompt)/100;
      lcd.setCursor(0, 1);
      char string[1];
      sprintf(string,"%d",time);
      lcd.print(time);
      }
      if (actionCompleted == 1)
      {
       rightSound();
      }
      else if(timeElapsed > easyMode && actionCompleted == 0)
      {
        gameOver();
      }
    }
    else if (action == 5)
    {
      lcdDisplay();
      lcd.print("TOUCH RIGHT");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //easyTimer();
      //Action 3 = Press BLUE Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        if (rightTouch == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
      timeElapsed = millis() - timeOfPrompt;
      int time = ((timeElapsed - timeOfPrompt)/100);
      lcd.setCursor(0, 1);
      char string[1];
      sprintf(string,"%d",time);
      lcd.print(time);
      }
      if (actionCompleted == 1)
      {
       rightSound();
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }
    }
    else if (action == 6)
    {
      lcdDisplay();
      lcd.print("TOUCH LEFT");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //easyTimer();
      //Action 3 = Press BLUE Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        if (leftTouch == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
       rightSound();
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }
    }
    else if (action == 7)
    {
      lcdDisplay();
      lcd.print("TOUCH UP");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //easyTimer();
      //Action 3 = Press BLUE Button  
      while (timeElapsed < easyMode && actionCompleted == 0)
      {
        readBtnStates();
        if (upTouch == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
       rightSound();
      }
      else if(timeElapsed > 700 && actionCompleted == 0)
      {
        gameOver();
      }
    }
  }
}//end this function

//Hard Mode
void keepPlayingHard()
{
  playing1 = 1;
  //while loop to keep running game until user has failed and "playing1" is set to zero
  while (playing1 != 0) 
  {   
    //pick an action to assign the user via a random number generator – upper bound is exclusive
    action = random(1, 8);
    actionCompleted = 0;
    if (action == 1)
    {
      lcdDisplay();
      lcd.print("PRESS RED");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 1 = Press Red Button  
      while (timeElapsed < hardMode && actionCompleted == 0)
      {
        readBtnStates();
        if (redState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(greenState == HIGH || blueState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
        rightSound();
      }
      else if(timeElapsed > 300 && actionCompleted == 0)
      {
        gameOver();
      }

    }
    //Action 2
    else if (action == 2)
    {
      lcdDisplay();
      lcd.print("PRESS GREEN"); 
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 1 = Press Red Button  
      while (timeElapsed < hardMode && actionCompleted == 0)
      {
        readBtnStates();
        if (greenState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || blueState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
        rightSound();
      }
      else if(timeElapsed > 300 && actionCompleted == 0)
      {
        gameOver();
      }
    }

    //Action 3
    else if (action == 3)
    {
      lcdDisplay();
      lcd.print("PRESS BLUE");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 3 = Press BLUE Button  
      while (timeElapsed < hardMode && actionCompleted == 0)
      {
        readBtnStates();
        if (blueState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || yellowState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
        rightSound();
      }
      else if(timeElapsed > 300 && actionCompleted == 0)
      {
        gameOver();
      }
    }

    //Action 4
    else if (action == 4)
    {
      lcdDisplay();
      lcd.print("PRESS YELLOW");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 3 = Press BLUE Button  
      while (timeElapsed < hardMode && actionCompleted == 0)
      {
        readBtnStates();
        if (yellowState == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
       rightSound();
      }
      else if(timeElapsed > 300 && actionCompleted == 0)
      {
        gameOver();
      }
    }
    else if (action == 5)
    {
      lcdDisplay();
      lcd.print("TOUCH RIGHT");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 3 = Press BLUE Button  
      while (timeElapsed < hardMode && actionCompleted == 0)
      {
        readBtnStates();
        if (rightTouch == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
       rightSound();
      }
      else if(timeElapsed > 300 && actionCompleted == 0)
      {
        gameOver();
      }
    }
    else if (action == 6)
    {
      lcdDisplay();
      lcd.print("TOUCH LEFT");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 3 = Press BLUE Button  
      while (timeElapsed < hardMode && actionCompleted == 0)
      {
        readBtnStates();
        if (leftTouch == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
       rightSound();
      }
      else if(timeElapsed > 300 && actionCompleted == 0)
      {
        gameOver();
      }
    }
    else if (action == 7)
    {
      lcdDisplay();
      lcd.print("TOUCH UP");
      timeOfPrompt = millis();
      timeElapsed = millis() - timeOfPrompt;
      //Action 3 = Press BLUE Button  
      while (timeElapsed < hardMode && actionCompleted == 0)
      {
        readBtnStates();
        if (upTouch == HIGH)
        {
          actionCompleted = 1;
          score = score + 1;
        }
        else if(redState == HIGH || greenState == HIGH || blueState == HIGH)
        {
          gameOver();
        }
        //recalculate timeElapsed
        timeElapsed = millis() - timeOfPrompt;
      }
      if (actionCompleted == 1)
      {
       rightSound();
      }
      else if(timeElapsed > 300 && actionCompleted == 0)
      {
        gameOver();
      }
    }
  }
}//end this function
>>>>>>> 9575410c229e6e76b75f994fdb20fef29326477c
