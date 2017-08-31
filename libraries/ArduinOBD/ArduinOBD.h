#ifndef ArduinOBD_h
#define ArduinOBD_h

#include "UTFT.h"
#include "Gauge.h"

class ArduinOBD : public UTFT
{
    public:
        ArduinOBD() : UTFT(R61581,38,39,40,41)
        {
            
        }
        int _windowWidth;
        int _windowHeight;
        Gauge _gauge;
        void init(byte orientation);
        void readTouchInput();
        int getCurrentGaugeType();
        void cycleGauges();
        void addButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight, String buttonText);
        void addLabel(int labelX, int labelY, String labelText);
        int getLabelWidth(String labelText);
        int getLabelHeight(String labelText);
        void drawGaugeNeedle(int angle, int needleLength);
        void drawDigitalVal(int val);
        void drawBoostGauge();
        void drawBoostNeedle(float psi, bool outputDigital);
        void drawMphGauge();
        void drawMphNeedle(int mph, bool outputDigital);
        void drawRpmGauge();
        void drawRpmNeedle(int rpm, bool outputDigital);
        void drawNextBackButtons();
    private:
        byte _orientation;
};

#endif