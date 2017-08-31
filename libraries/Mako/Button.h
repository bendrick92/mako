#ifndef Button_h
#define Button_h

class Button
{
    public:
        Button()
        {
            _x1 = 0;
            _y1 = 0;
            _width = 0;
            _height = 0;
            _label = "";
            _buttonAction = 0;
        }
        int _x1;
        int _y1;
        int _width;
        int _height;
        String _label;
        int _buttonAction;
        void init(int x1, int y1, int width, int height, String label, int buttonAction);
        bool clickWithinBounds(int x, int y);
};

#endif