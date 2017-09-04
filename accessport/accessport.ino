#include <Mako.h>

Mako mako{};

void setup() {    
  mako.init(PORTRAIT, false);
}

void loop() {
  mako.process();
  mako.readTouchInput();
}
