#include <speaker.h>

Speaker::Speaker() {}

void Speaker::gameOver() {
  tone(6, 100, 100);
  delay(100);
  noTone(6);
}

void correctAction() {
  tone(6, 5000, 50); //tone(pin, freq, duration)
  delay(50);
  noTone(6);
}