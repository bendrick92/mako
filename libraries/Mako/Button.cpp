#include "Arduino.h"
#include "Button.h"

void Button::init(int x1, int y1, int width, int height, String label, int buttonAction)
{
    _x1 = x1;
    _y1 = y1;
    _width = width;
    _height = height;
    _label = label;
    _buttonAction = buttonAction;
}

bool Button::clickWithinBounds(int x, int y)
{
    int x2 = _x1 + _width;
    int y2 = _y1 + _height;

    if (x >= _x1 && x <= x2 && y >= _y1 && y <= y2)
    {
        return true;
    }
    else {
        return false;
    }
}