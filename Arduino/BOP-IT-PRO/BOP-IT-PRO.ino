#include <Talkie.h>
#include <TalkieUtils.h>
#include <Vocab_US_Large.h>
#include <Vocab_US_Acorn.h>
#include <Vocab_Special.h>
#include <Vocab_US_TI99.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

//Buttons define
#define btnBlue 2
#define btnRed 3
#define btnYellow 4
#define btnGreen 5

int blueState = 0;
int redState = 0;
int yellowState = 0;
int greenState = 0;

//Speaker
// Text-to-speech
Talkie voz;
// SD card
TMRpcm tmrpcm;
#define SD_ChipSelectPin 4

//Touch Sensor
#define TS1 2
#define TS2 3
#define TS3 4
#define TS4 5

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
  
  Serial.begin(9600);
  sd_check();  
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
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Welcome to");     // print message at (0, 0)
  lcd.setCursor(5, 1);         // move cursor to   (5, 1)
  lcd.print("BOP-IT PRO!");    // print message at (5, 1)
}

// SD card sound functions
void sd_check()
{
  // check for SD card present
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD card failed");
    return;
  }
}

void play_sound(int s) {
  // select correct file
  char* music = "";
  switch (s) {
    case 0:
      music = "game_over";
      break;
    case 1:
      music = "bell_correct-answer";
      break;
    case 2:
      music = "buzzer_wrong-answer";
      break;
    default:
      music = "";
  }

  // play music, output in terminal if it is working
  if (Serial.available()) { 
    // send p over serial to start playback   
    if (Serial.read() == 'p') {
      tmrpcm.play(music);
    }
  }

  // end function
  return;
}

//Start Message
void start()
{
  lcd.setCursor(0, 0);
  lcd.print("Press & hold any");
  lcd.setCursor(0, 1);
  lcd.print("button to start");
  voz.say(spt_PRESS);
  voz.say(spt_AND);
  voz.say(sp4_HOLD);
  voz.say(spt_ANY);
  voz.say(sp2_BUTTON);
  voz.say(sp4_TO);
  voz.say(sp4_START);
  delay(50);
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
    voz.say(sp4_YOU);
    voz.say(spa_INPUT);
    voz.say(sp4_LEVEL);
    voz.say(sp3_RED);
    delay(100);
    //keepPlayingHard();
}
void easyGameStart()
{
    lcdDisplay();
    lcd.print("  YOU SELECTED  ");
    lcd.setCursor(0, 1);
    lcd.print("   EASY LEVEL   ");
    voz.say(sp4_YOU);
    voz.say(spa_INPUT);
    voz.say(sp4_LEVEL);
    voz.say(sp3_GREEN);
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
  
  play_sound(0);
  tone(6, 100, 100);
  delay(100);
  noTone(6);
  finalScore = score;
  char scoreString[10];
  sprintf(scoreString,"%d",finalScore);
  lcdDisplay();
  lcd.print("GAME OVER!");
  voz.say(spt_NICE_TRY);
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
      voz.say(sp2_PRESS);
      voz.say(sp3_RED);
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
        play_sound(1);
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
      voz.say(sp2_PRESS);
      voz.say(sp3_GREEN);      
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
        play_sound(1);
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
      voz.say(sp2_PRESS);
      voz.say(spt_BLUE);
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
        play_sound(1);
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
        play_sound(1);
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
