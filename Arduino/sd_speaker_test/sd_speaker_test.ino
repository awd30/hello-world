#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

#define SD_ChipSelectPin 4    // set pin for the SD chip select (macro --> constant)
TMRpcm tmrpcm;                // create an object for use in this sketch

void setup() {
  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  tmrpcm.play("game_over"); //the sound file "music" will play each time the arduino powers up, or is reset
}

void loop() {  
  if(Serial.available()) {    
    if (Serial.read() == 'p') { //send the letter p over the serial monitor to start playback
      tmrpcm.play("music");
    }
  }
}
