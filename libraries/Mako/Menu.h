#ifndef Menu_h
#define Menu_h

#include "Button.h"

typedef enum {
    MAIN = 0
} MENU_TYPES;

class Menu
{
    public:
        Menu()
        {
            _menuType = MAIN;
        }

        MENU_TYPES _menuType;
        Button _buttons[10];
        void init(MENU_TYPES menuType);
};

#endif