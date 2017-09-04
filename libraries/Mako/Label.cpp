#include "Arduino.h"
#include "Label.h"

void Label::init(int x, int y, String text)
{
    _x = x;
    _y = y;
    _text = text;
}