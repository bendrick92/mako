#include "Arduino.h"
#include "Gauge.h"
#include "math.h"

void Gauge::init(int centerX, int centerY, int radius, int gaugeType)
{
    _centerX = centerX;
    _centerY = centerY;
    _radius = radius;
    _gaugeType = gaugeType;
}

int Gauge::generateNeedleX(int angle, int needleLength)
{
    return calculateGaugeEdgeX(angle, needleLength);
}

int Gauge::generateNeedleY(int angle, int needleLength)
{
    return calculateGaugeEdgeY(angle, needleLength);
}

int Gauge::generateLabelX(int labelWidth, int angle, int padding)
{
    int labelX = calculateGaugeEdgeX(angle, _radius + padding);

    if (angle == 0 || angle == 360)
    {
        labelX = labelX;
    }
    else if (angle > 0 && angle < 90)
    {
        labelX = labelX;
    }
    else if (angle == 90)
    {
        labelX = labelX - (labelWidth / 2);
    }
    else if (angle > 90 && angle < 180)
    {
        labelX = labelX - labelWidth;
    }
    else if (angle == 180)
    {
        labelX = labelX - labelWidth;
    }
    else if (angle > 180 && angle < 270)
    {
        labelX = labelX - labelWidth;
    }
    else if (angle == 270) {
        labelX = labelX - (labelWidth / 2);
    }
    else if (angle > 270 && angle < 360)
    {
        labelX = labelX;
    }

    return labelX;
}

int Gauge::generateLabelY(int labelHeight, int angle, int padding)
{
    int labelY = calculateGaugeEdgeY(angle, _radius + padding);

    if (angle == 0 || angle == 360)
    {
        labelY = labelY - (labelHeight / 2);
    }
    else if (angle > 0 && angle < 90)
    {
        labelY = labelY - labelHeight;
    }
    else if (angle == 90)
    {
        labelY = labelY - labelHeight;
    }
    else if (angle > 90 && angle < 180)
    {
        labelY = labelY - labelHeight;
    }
    else if (angle == 180)
    {
        labelY = labelY - (labelHeight / 2);
    }
    else if (angle > 180 && angle < 270)
    {
        labelY = labelY;
    }
    else if (angle == 270) {
        labelY = labelY;
    }
    else if (angle > 270 && angle < 360)
    {
        labelY = labelY;
    }

    return labelY;
}

int Gauge::calculateGaugeEdgeX(int angle)
{
    double radians = angle * -0.0175;
    return _centerX + _radius * cos(radians);
}

int Gauge::calculateGaugeEdgeY(int angle)
{
    double radians = angle * -0.0175;
    return _centerY + _radius * sin(radians);
}

int Gauge::calculateGaugeEdgeX(int angle, int radius)
{
    double radians = angle * -0.0175;
    return _centerX + radius * cos(radians);
}

int Gauge::calculateGaugeEdgeY(int angle, int radius)
{
    double radians = angle * -0.0175;
    return _centerY + radius * sin(radians);
}

int Gauge::translatePsiToAngle(float psi)
{
    if (psi < -15.0)
    {
        return 180;
    }
    else if (psi >= -15.0 && psi < 30.0)
    {
        return 90 + (psi * -6);
    }
    else
    {
        return -60;
    }
}

int Gauge::translateMphToAngle(int mph)
{
    if (mph < 0)
    {
        return 180;
    }
    else if (mph >= 0 && mph < 240)
    {
        return 180 + (-1 * mph * 1.5);
    }
    else
    {
        return 360;
    }
}

int Gauge::translateRpmToAngle(int rpm)
{
    if (rpm < 0)
    {
        return 180;
    }
    else if (rpm >= 0 && rpm < 7500)
    {
        return 180 + (-1 * rpm * 0.03);
    }
    else
    {
        return -30;
    }
}

int Gauge::translateThrottlePercToAngle(int throttlePerc)
{
    if (throttlePerc < 0)
    {
        return 180;
    }
    else if (throttlePerc >= 0 && throttlePerc < 100)
    {
        return 180 + (throttlePerc * -3.6);
    }
    else
    {
        return 360;
    }
}