#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

BopItPro bopit;

void setup() {
    bopit = BopItPro();
}

void loop() {
    bopit.boot();
}