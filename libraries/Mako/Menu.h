#ifndef Menu_h
#define Menu_h

#include "Button.h"

class Menu
{
    public:
        Menu()
        {

        }

        Button _buttons[10];
        void init();
};

#endif