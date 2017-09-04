#ifndef Label_h
#define Label_h

class Label
{
    public:
        Label()
        {
            _x = 0;
            _y = 0;
            _text = "";
        }
        int _x;
        int _y;
        String _text;
        void init(int x, int y, String label);
};

#endif