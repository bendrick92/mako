#include <Mako.h>

Mako mako{};

void setup() {    
  mako.init(PORTRAIT, true);
}

void loop() {
  mako.process();
  mako.readTouchInput();
}
