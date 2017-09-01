#include <Mako.h>

Mako mako{};

bool testMode = false;

void setup() {  
  randomSeed(analogRead(0));
  
  mako.init(PORTRAIT, testMode);
}

void loop() {
  mako.process();

  mako.readTouchInput();
}
