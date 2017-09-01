#ifndef Mako_h
#define Mako_h

#include "UTFT.h"
#include "Gauge.h"
#include "Menu.h"
#include "OBD2UART.h"

class Mako : public UTFT
{
    public:
        Mako() : UTFT(R61581,38,39,40,41)
        {
            
        }
        COBD _obd;
        Gauge _gauge;
        Menu _menu;
        void init(byte orientation, bool testMode);
        void process();
        void setupGaugeLayout();
        void readTouchInput();
        void processButtonClick(int buttonAction);
        int getCurrentGaugeType();
        void cycleToPrevGauge();
        void cycleToNextGauge();
        void addButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight, String buttonText);
        void addLabel(int labelX, int labelY, String labelText);
        int getLabelWidth(String labelText);
        int getLabelHeight(String labelText);
        void drawGaugeNeedle(int angle, int needleLength);
        void drawDigitalVal(int val);
        void drawTitleMessage(String message);
        void drawFooterMessage(String message);
        void drawCenteredMessage(String message);
        void drawDefaultGauge();
        void drawBoostGauge();
        void drawBoostNeedle(float psi, bool outputDigital);
        void drawMphGauge();
        void drawMphNeedle(int mph, bool outputDigital);
        void drawRpmGauge();
        void drawRpmNeedle(int rpm, bool outputDigital);
        void drawThrottleGauge();
        void drawThrottleNeedle(int throttlePerc, bool outputDigital);
        void drawMainMenu();
        void drawGauge(int gaugeType, String title);
        void drawMenu(int menuType, String title);
        void resetScreen();
    private:
        byte _orientation;
        bool _testMode;
        int _windowWidth;
        int _windowHeight;
};

#endif