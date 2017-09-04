#ifndef Gauge_h
#define Gauge_h

#include "Button.h"
#include "Label.h"

typedef enum {
    BOOST_PSI = 0,
    SPEED_MPH = 1,
    ENGINE_RPM = 2,
    THROTTLE_PERC = 3
} GAUGE_TYPES;

class Gauge
{
    public:
        Gauge()
        {
            _gaugeType = BOOST_PSI;
            _centerX = 0;
            _centerY = 0;
            _radius = 0;
            _needleX = 0;
            _needleY = 0;
        }

        GAUGE_TYPES _gaugeType;
        int _centerX;
        int _centerY;
        int _radius;
        int _needleX;
        int _needleY;
        Button _buttons[10];
        Label _labels[20];
        void init(int centerX, int centerY, int radius, GAUGE_TYPES gaugeType);
        void addLabel(String label, int angle);
        int generateNeedleX(int angle, int needleLength);
        int generateNeedleY(int angle, int needleLength);
        int generateLabelX(int labelWidth, int angle, int padding);
        int generateLabelY(int labelHeight, int angle, int padding);
        int translatePsiToAngle(float psi);
        int translateMphToAngle(int mph);
        int translateRpmToAngle(int rpm);
        int translateThrottlePercToAngle(int throttlePerc);
    private:
        int calculateGaugeEdgeX(int angle);
        int calculateGaugeEdgeY(int angle);
        int calculateGaugeEdgeX(int angle, int radius);
        int calculateGaugeEdgeY(int angle, int radius);
};

#endif