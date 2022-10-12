//hello-world
//LCD Display Code
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
int colorR = 255;
int colorG = 255;
int colorB = 255;

void setup() {
  Serial.begin(9600);
 /* pinMode(pinTouch, INPUT);
  pinMode(pinD-Pad, INPUT);
  pinMode(pinPotentiometer, INPUT);
  pinMode(pinFlipButton, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  */
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  initialize();
  delay(1000);
}
void init() 
{
  // put your setup code here, to run once:
  lcd.clear();
  lcd.print("BOP-IT PRO 2022");
  //lcd.setCursor(0,1); // ---- | ---- | ---- | ----
  lcd.print("PRESS ANY KEY TO BEGIN");
  //digitalWrite(13, LOW);
  //digitalWrite(12, LOW);
  //digitalWrite(11, LOW);
  //int counter = 0;
  //int delayCount = 5000;
  //return;
}

void loop() {
  // put your main code here, to run repeatedly:

}
