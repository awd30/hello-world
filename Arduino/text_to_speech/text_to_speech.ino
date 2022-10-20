#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"

Talkie voz;

void setup() {}

void loop() {
  voz.say(spPAUSE2);
  voz.say(sp2_HELLO);
}
