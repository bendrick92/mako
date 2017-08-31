#include "UTFT.h"
#include "math.h"
#include "ArduinOBD.h"
#include "Gauge.h"
#include "touch.h"

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

void ArduinOBD::init(byte orientation)
{
    _orientation = orientation;
    InitLCD(orientation);
    _windowWidth = getDisplayXSize();
    _windowHeight = getDisplayYSize();
    touch.init();

    drawBoostGauge();
}

void ArduinOBD::readTouchInput()
{
    int touchX;
    int touchY;

    if (touch.read(touchX,touchY))
    {
        cycleGauges();
    }
}

int ArduinOBD::getCurrentGaugeType()
{
    return _gauge._gaugeType;
}

void ArduinOBD::cycleGauges()
{
    if (_gauge._gaugeType == 0)
    {
        drawMphGauge();
    }
    else if (_gauge._gaugeType == 1)
    {
        drawRpmGauge();
    }
    else if (_gauge._gaugeType == 2)
    {
        drawBoostGauge();
    }
}

void ArduinOBD::addButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight, String buttonText)
{
    int buttonX2 = buttonX + buttonWidth;
    int buttonY2 = buttonY + buttonHeight;

    int buttonMidX = buttonX2 - (0.5 * buttonWidth);
    int buttonMidY = buttonY2 - (0.5 * buttonHeight);

    setColor(255,255,255);
    drawRect(buttonX,buttonY,buttonX2,buttonY2);

    setFont(BigFont);
    print(buttonText,buttonMidX,buttonMidY);
}

void ArduinOBD::addLabel(int labelX, int labelY, String labelText)
{
    print(labelText,labelX,labelY);
}

// Requires font type to be set before being called
// NOTE: "1" does not have the same width as "0"; is there a monospaced param/font?
int ArduinOBD::getLabelWidth(String labelText)
{
    int fontWidth;
    int labelLength = labelText.length();

    fontWidth = getFontXsize();

    return labelLength * fontWidth;
}

int ArduinOBD::getLabelHeight(String labelText)
{
    int fontHeight = getFontYsize();

    return fontHeight;
}

void ArduinOBD::drawGaugeNeedle(int angle, int needleLength)
{   
    // Overwrite last needle drawn on gauge
    setColor(0,0,0);
    drawLine(_gauge._centerX,_gauge._centerY,_gauge._needleX,_gauge._needleY);
    
    // Calculate new needle coordinates
    _gauge._needleX = _gauge.generateNeedleX(angle,needleLength);
    _gauge._needleY = _gauge.generateNeedleY(angle,needleLength);

    // Draw new needle
    setColor(255,255,255);
    drawLine(_gauge._centerX,_gauge._centerY,_gauge._needleX,_gauge._needleY);
}

void ArduinOBD::drawDigitalVal(int val)
{
    setFont(BigFont);
    printNumI(val,CENTER,40,4,' ');
}

void ArduinOBD::drawBoostGauge()
{
    int centerX = _windowWidth / 2;
    int centerY = _windowHeight / 2;
    int radius = 100;
    int padding = 15;
    int labelX;
    int labelY;

    fillScr(0,0,0);

    setColor(255,255,255);
    drawCircle(centerX,centerY,radius);

    setColor(255,255,255);
    setFont(SmallFont);

    Gauge boostGauge{};
    boostGauge.init(centerX,centerY,radius,0);
    _gauge = boostGauge;

    labelX = _gauge.generateLabelX(getLabelWidth("25"),300,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("25"),300,padding);
    addLabel(labelX,labelY,"25");
    labelX = _gauge.generateLabelX(getLabelWidth("20"),330,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("20"),330,padding);
    addLabel(labelX,labelY,"20");
    labelX = _gauge.generateLabelX(getLabelWidth("15"),0,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("15"),0,padding);
    addLabel(labelX,labelY,"15");
    labelX = _gauge.generateLabelX(getLabelWidth("10"),30,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("10"),30,padding);
    addLabel(labelX,labelY,"10");
    labelX = _gauge.generateLabelX(getLabelWidth("5"),60,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("5"),60,padding);
    addLabel(labelX,labelY,"5");
    labelX = _gauge.generateLabelX(getLabelWidth("0"),90,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("0"),90,padding);
    addLabel(labelX,labelY,"0");
    labelX = _gauge.generateLabelX(getLabelWidth("-5"),120,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("-5"),120,padding);
    addLabel(labelX,labelY,"-5");
    labelX = _gauge.generateLabelX(getLabelWidth("-10"),150,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("-10"),150,padding);
    addLabel(labelX,labelY,"-10");
    labelX = _gauge.generateLabelX(getLabelWidth("-15"),180,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("-15"),180,padding);
    addLabel(labelX,labelY,"-15");
}

void ArduinOBD::drawBoostNeedle(float psi, bool outputDigital)
{
    int needleLength = 85;
    int angle = _gauge.translatePsiToAngle(psi);

    drawGaugeNeedle(angle,needleLength);

    if (outputDigital)
    {
        drawDigitalVal(psi);
    }
}

void ArduinOBD::drawMphGauge()
{
    int centerX = _windowWidth / 2;
    int centerY = _windowHeight / 2;
    int radius = 100;
    int padding = 15;
    int labelX;
    int labelY;

    fillScr(0,0,0);

    setColor(255,255,255);
    drawCircle(centerX,centerY,radius);

    setColor(255,255,255);
    setFont(SmallFont);

    Gauge mphGauge{};
    mphGauge.init(centerX,centerY,radius,1);
    _gauge = mphGauge;

    labelX = _gauge.generateLabelX(getLabelWidth("0"),180,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("0"),180,padding);
    addLabel(labelX,labelY,"0");
    labelX = _gauge.generateLabelX(getLabelWidth("10"),165,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("10"),165,padding);
    addLabel(labelX,labelY,"10");
    labelX = _gauge.generateLabelX(getLabelWidth("20"),150,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("20"),150,padding);
    addLabel(labelX,labelY,"20");
    labelX = _gauge.generateLabelX(getLabelWidth("30"),135,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("30"),135,padding);
    addLabel(labelX,labelY,"30");
    labelX = _gauge.generateLabelX(getLabelWidth("40"),120,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("40"),120,padding);
    addLabel(labelX,labelY,"40");
    labelX = _gauge.generateLabelX(getLabelWidth("50"),105,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("50"),105,padding);
    addLabel(labelX,labelY,"50");
    labelX = _gauge.generateLabelX(getLabelWidth("60"),90,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("60"),90,padding);
    addLabel(labelX,labelY,"60");
    labelX = _gauge.generateLabelX(getLabelWidth("70"),75,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("70"),75,padding);
    addLabel(labelX,labelY,"70");
    labelX = _gauge.generateLabelX(getLabelWidth("80"),60,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("80"),60,padding);
    addLabel(labelX,labelY,"80");
    labelX = _gauge.generateLabelX(getLabelWidth("90"),45,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("90"),45,padding);
    addLabel(labelX,labelY,"90");
    labelX = _gauge.generateLabelX(getLabelWidth("100"),30,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("100"),30,padding);
    addLabel(labelX,labelY,"100");
    labelX = _gauge.generateLabelX(getLabelWidth("110"),15,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("110"),15,padding);
    addLabel(labelX,labelY,"110");
    labelX = _gauge.generateLabelX(getLabelWidth("120"),0,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("120"),0,padding);
    addLabel(labelX,labelY,"120");
}

void ArduinOBD::drawMphNeedle(int mph, bool outputDigital)
{
    int needleLength = 85;
    int angle = _gauge.translateMphToAngle(mph);

    drawGaugeNeedle(angle,needleLength);

    if (outputDigital)
    {
        drawDigitalVal(mph);
    }
}

void ArduinOBD::drawRpmGauge()
{
    int centerX = _windowWidth / 2;
    int centerY = _windowHeight / 2;
    int radius = 100;
    int padding = 15;
    int labelX;
    int labelY;

    fillScr(0,0,0);

    setColor(255,255,255);
    drawCircle(centerX,centerY,radius);

    setColor(255,255,255);
    setFont(SmallFont);

    Gauge rpmGauge{};
    rpmGauge.init(centerX,centerY,radius,2);
    _gauge = rpmGauge;

    labelX = _gauge.generateLabelX(getLabelWidth("0"),180,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("0"),180,padding);
    addLabel(labelX,labelY,"0");
    labelX = _gauge.generateLabelX(getLabelWidth("1"),150,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("1"),150,padding);
    addLabel(labelX,labelY,"1");
    labelX = _gauge.generateLabelX(getLabelWidth("2"),120,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("2"),120,padding);
    addLabel(labelX,labelY,"2");
    labelX = _gauge.generateLabelX(getLabelWidth("3"),90,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("3"),90,padding);
    addLabel(labelX,labelY,"3");
    labelX = _gauge.generateLabelX(getLabelWidth("4"),60,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("4"),60,padding);
    addLabel(labelX,labelY,"4");
    labelX = _gauge.generateLabelX(getLabelWidth("5"),30,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("5"),30,padding);
    addLabel(labelX,labelY,"5");
    labelX = _gauge.generateLabelX(getLabelWidth("6"),0,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("6"),0,padding);
    addLabel(labelX,labelY,"6");
    labelX = _gauge.generateLabelX(getLabelWidth("7"),330,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("7"),330,padding);
    addLabel(labelX,labelY,"7");
    labelX = _gauge.generateLabelX(getLabelWidth("8"),300,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("8"),300,padding);
    addLabel(labelX,labelY,"8");
    labelX = _gauge.generateLabelX(getLabelWidth("9"),270,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("9"),270,padding);
    addLabel(labelX,labelY,"9");
}

void ArduinOBD::drawRpmNeedle(int rpm, bool outputDigital)
{
    int needleLength = 85;
    int angle = _gauge.translateRpmToAngle(rpm);

    drawGaugeNeedle(angle,needleLength);

    if (outputDigital)
    {
        drawDigitalVal(rpm);
    }
}

void ArduinOBD::drawNextBackButtons()
{
    addButton(20,20,50,30,"Prev");
}