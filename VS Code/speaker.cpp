
Speaker::Speaker() {
    
}

void Speaker::sd_check()
{
  // check for SD card present
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD card failed");
    return;
  }
}

void Speaker::play_sound(int s) {
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