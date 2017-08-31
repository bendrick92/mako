#include "UTFT.h"
#include "math.h"
#include "Mako.h"
#include "Gauge.h"
#include "touch.h"

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

void Mako::init(byte orientation, bool testMode)
{
    _testMode = testMode;
    _orientation = orientation;
    InitLCD(orientation);
    _windowWidth = getDisplayXSize();
    _windowHeight = getDisplayYSize();

    touch.init();

    resetScreen();
    drawCenteredMessage("Initializing...");
}

void Mako::readTouchInput()
{
    int x;
    int y;

    if (touch.read(x,y))
    {
        
        /*Serial.print(_buttons[0]._x1);
        Serial.print(",");
        Serial.print(_buttons[0]._y1);
        Serial.print(":");
        Serial.print(_buttons[0]._x1 + _buttons[0]._width);
        Serial.print(",");
        Serial.print(_buttons[0]._y1 + _buttons[0]._height);
        Serial.print(" ");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println();
        
        if (_buttons[0].clickWithinBounds(x,y))
        {
            cycleToPrevGauge();
        }
        else if (_buttons[1].clickWithinBounds(x,y))
        {
            cycleToNextGauge();
        }*/
        

        for (int a = 0; a < sizeof(_gauge._buttons)/sizeof(_gauge._buttons[0]); a = a + 1) {
            Serial.print(_gauge._buttons[a]._x1);
            Serial.print(",");
            Serial.print(_gauge._buttons[a]._y1);
            Serial.print(":");
            Serial.print(_gauge._buttons[a]._x1 + _gauge._buttons[a]._width);
            Serial.print(",");
            Serial.print(_gauge._buttons[a]._y1 + _gauge._buttons[a]._height);
            Serial.print(" ");
            Serial.print(x);
            Serial.print(",");
            Serial.print(y);
            Serial.println();
            if (_gauge._buttons[a].clickWithinBounds(x,y)) {
                processButtonClick(_gauge._buttons[a]._buttonAction);
            }
        }
    }
}

void Mako::processButtonClick(int buttonAction)
{
    switch (buttonAction) {
        case 0:
            drawDefaultGauge();
            break;
        case 1:
            drawBoostGauge();
            break;
        case 2:
            drawMphGauge();
            break;
        case 3:
            drawRpmGauge();
            break;
        case 4:
            drawThrottleGauge();
            break;
        case 5:
            cycleToPrevGauge();
            break;
        case 6:
            cycleToNextGauge();
            break;
        case 7:
            drawMenu();
            break;
    }
}

int Mako::getCurrentGaugeType()
{
    return _gauge._gaugeType;
}

void Mako::cycleToPrevGauge()
{
    if (_gauge._gaugeType == 0)
    {
        drawThrottleGauge();
    }
    else if (_gauge._gaugeType == 1)
    {
        drawBoostGauge();
    }
    else if (_gauge._gaugeType == 2)
    {
        drawMphGauge();
    }
    else if (_gauge._gaugeType == 3)
    {
        drawRpmGauge();
    }
}

void Mako::cycleToNextGauge()
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
        drawThrottleGauge();
    }
    else if (_gauge._gaugeType == 3)
    {
        drawBoostGauge();
    }
}

void Mako::addButton(int buttonX, int buttonY, int buttonWidth, int buttonHeight, String buttonText)
{
    int buttonX2 = buttonX + buttonWidth;
    int buttonY2 = buttonY + buttonHeight;

    int buttonTextX = buttonX2 - (0.5 * buttonWidth) - (getLabelWidth(buttonText) / 2);
    int buttonTextY = buttonY2 - (0.5 * buttonHeight) - (getLabelHeight(buttonText) / 2);

    setColor(255,255,255);
    drawRect(buttonX,buttonY,buttonX2,buttonY2);

    setFont(SmallFont);
    print(buttonText,buttonTextX,buttonTextY);
}

void Mako::addLabel(int labelX, int labelY, String labelText)
{
    print(labelText,labelX,labelY);
}

int Mako::getLabelWidth(String labelText)
{
    int fontWidth;
    int labelLength = labelText.length();

    fontWidth = getFontXsize();

    return labelLength * fontWidth;
}

int Mako::getLabelHeight(String labelText)
{
    int fontHeight = getFontYsize();

    return fontHeight;
}

void Mako::drawGaugeNeedle(int angle, int needleLength)
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

void Mako::drawDigitalVal(int val)
{
    setColor(255,255,255);
    setFont(BigFont);
    printNumI(val,CENTER,40,4,' ');
}

void Mako::drawTitleMessage(String message)
{
    int centerX = _windowWidth / 2;
    
    int messageOffsetX = getLabelWidth(message) / 2;

    int messageX = centerX - messageOffsetX;
    int messageY = 0;

    setColor(255,255,255);
    setFont(SmallFont);
    print(message,messageX,messageY);
}

void Mako::drawFooterMessage(String message)
{
    int centerX = _windowWidth / 2;
    
    int messageOffsetX = getLabelWidth(message) / 2;
    int messageHeight = getLabelHeight(message);

    int messageX = centerX - messageOffsetX;
    int messageY = _windowHeight - messageHeight;

    setColor(255,255,255);
    setFont(SmallFont);
    print(message,messageX,messageY);
}

void Mako::drawCenteredMessage(String message)
{
    int centerX = _windowWidth / 2;
    int centerY = _windowHeight / 2;

    int messageOffsetX = getLabelWidth(message) / 2;
    int messageOffsetY = getLabelHeight(message) / 2;

    int messageX = centerX - messageOffsetX;
    int messageY = centerY - messageOffsetY;

    setColor(255,255,255);
    setFont(SmallFont);
    print(message,messageX,messageY);
}

void Mako::drawDefaultGauge()
{
    drawBoostGauge();
}

void Mako::drawBoostGauge()
{    
    int centerX = _windowWidth / 2;
    int centerY = _windowHeight / 2;
    int radius = 100;
    int padding = 15;
    int labelX;
    int labelY;

    resetScreen();

    drawTitleMessage("BOOST");

    setColor(255,255,255);
    drawCircle(centerX,centerY,radius);

    setColor(255,255,255);
    setFont(SmallFont);

    Gauge boostGauge{};
    boostGauge.init(centerX,centerY,radius,0);
    _gauge = boostGauge;

    addNextBackButtons();
    addMenuButton();
    drawGaugeButtons();

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

void Mako::drawBoostNeedle(float psi, bool outputDigital)
{
    int needleLength = 85;
    int angle = _gauge.translatePsiToAngle(psi);

    drawGaugeNeedle(angle,needleLength);

    if (outputDigital)
    {
        drawDigitalVal(psi);
    }
}

void Mako::drawMphGauge()
{
    int centerX = _windowWidth / 2;
    int centerY = _windowHeight / 2;
    int radius = 100;
    int padding = 15;
    int labelX;
    int labelY;

    resetScreen();

    drawTitleMessage("MPH");

    setColor(255,255,255);
    drawCircle(centerX,centerY,radius);

    setColor(255,255,255);
    setFont(SmallFont);

    Gauge mphGauge{};
    mphGauge.init(centerX,centerY,radius,1);
    _gauge = mphGauge;

    addNextBackButtons();
    addMenuButton();
    drawGaugeButtons();

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

void Mako::drawMphNeedle(int mph, bool outputDigital)
{
    int needleLength = 85;
    int angle = _gauge.translateMphToAngle(mph);

    drawGaugeNeedle(angle,needleLength);

    if (outputDigital)
    {
        drawDigitalVal(mph);
    }
}

void Mako::drawRpmGauge()
{    
    int centerX = _windowWidth / 2;
    int centerY = _windowHeight / 2;
    int radius = 100;
    int padding = 15;
    int labelX;
    int labelY;

    resetScreen();

    drawTitleMessage("RPM");    

    setColor(255,255,255);
    drawCircle(centerX,centerY,radius);

    setColor(255,255,255);
    setFont(SmallFont);

    Gauge rpmGauge{};
    rpmGauge.init(centerX,centerY,radius,2);
    _gauge = rpmGauge;

    addNextBackButtons();
    addMenuButton();
    drawGaugeButtons();

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

void Mako::drawRpmNeedle(int rpm, bool outputDigital)
{
    int needleLength = 85;
    int angle = _gauge.translateRpmToAngle(rpm);

    drawGaugeNeedle(angle,needleLength);

    if (outputDigital)
    {
        drawDigitalVal(rpm);
    }
}

void Mako::drawThrottleGauge()
{
    int centerX = _windowWidth / 2;
    int centerY = _windowHeight / 2;
    int radius = 100;
    int padding = 15;
    int labelX;
    int labelY;

    resetScreen();

    drawTitleMessage("THROTTLE");

    setColor(255,255,255);
    drawCircle(centerX,centerY,radius);

    setColor(255,255,255);
    setFont(SmallFont);

    Gauge throttleGauge{};
    throttleGauge.init(centerX,centerY,radius,3);
    _gauge = throttleGauge;
    
    addNextBackButtons();
    addMenuButton();
    drawGaugeButtons();

    labelX = _gauge.generateLabelX(getLabelWidth("0"),180,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("0"),180,padding);
    addLabel(labelX,labelY,"0");
    labelX = _gauge.generateLabelX(getLabelWidth("25"),90,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("25"),90,padding);
    addLabel(labelX,labelY,"25");
    labelX = _gauge.generateLabelX(getLabelWidth("50"),0,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("50"),0,padding);
    addLabel(labelX,labelY,"50");
    labelX = _gauge.generateLabelX(getLabelWidth("75"),270,padding);
    labelY = _gauge.generateLabelY(getLabelHeight("75"),270,padding);
    addLabel(labelX,labelY,"75");
}

void Mako::drawThrottleNeedle(int throttlePerc, bool outputDigital)
{
    int needleLength = 85;
    int angle = _gauge.translateThrottlePercToAngle(throttlePerc);

    drawGaugeNeedle(angle,needleLength);

    if (outputDigital)
    {
        drawDigitalVal(throttlePerc);
    }
}

void Mako::drawMenu()
{
    resetScreen();

    drawTitleMessage("MENU");

    Gauge menuGauge{};
    _gauge = menuGauge;

    addMenuButtons();
    drawGaugeButtons();
}

void Mako::addNextBackButtons()
{
    int buttonWidth = 50;
    int buttonHeight = 30;
    int marginX = 20;
    int backButtonX =  marginX;
    int nextButtonX = _windowWidth - buttonWidth - marginX;
    int buttonY = _windowHeight - 50;

    Button backButton{};
    backButton.init(marginX,buttonY,buttonWidth,buttonHeight,"Prev",5);
    _gauge._buttons[0] = backButton;

    Button nextButton{};
    nextButton.init(nextButtonX,buttonY,buttonWidth,buttonHeight,"Next",6);
    _gauge._buttons[1] = nextButton;
}

void Mako::addMenuButton()
{
    int buttonWidth = 50;
    int buttonHeight = 30;
    int buttonX = 20;
    int buttonY = 50;

    Button menuButton{};
    menuButton.init(buttonX,buttonY,buttonWidth,buttonHeight,"Menu",7);
    _gauge._buttons[3] = menuButton;
}

void Mako::addMenuButtons()
{
    int buttonWidth = 50;
    int buttonHeight = 30;
    int exitButtonX = _windowWidth - buttonWidth - 20;
    int exitButtonY = 50;

    Button exitButton{};
    exitButton.init(exitButtonX,exitButtonY,buttonWidth,buttonHeight,"Exit",0);
    _gauge._buttons[4] = exitButton;
}

void Mako::drawGaugeButtons()
{
    for (int x = 0; x < sizeof(_gauge._buttons)/sizeof(_gauge._buttons[0]); x = x + 1) {
        addButton(_gauge._buttons[x]._x1,_gauge._buttons[x]._y1,_gauge._buttons[x]._width,_gauge._buttons[x]._height,_gauge._buttons[x]._label);
    }
}

void Mako::resetScreen()
{
    fillScr(0,0,0);

    if (_testMode) {
        drawFooterMessage("TEST MODE");
    }
}