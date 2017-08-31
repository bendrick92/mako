#include <Mako.h>
#include <OBD2UART.h>
#include <SD.h>

Mako mako{};
COBD obd;

bool testMode = false;
int counter = 0;

void setup() {
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  
  mako.init(PORTRAIT, testMode);

  obd.begin();
  obd.init(); // Should timeout after 5 seconds or so and move on; may need to implement some retries
  if (obd.getState() != 2) {  // May want to have this wait for a response before checking?
    mako._testMode = true;
  }

  mako.drawDefaultGauge();
}

void loop() {
  // 0 = Boost
  // 1 = MPH
  // 2 = RPM
  // 3 = Throttle
  int currentGaugeType = mako.getCurrentGaugeType();
  if (currentGaugeType == 0) {
    int intakeKpa = 0;
    int atmosKpa = 0;
    float boostPsi = 0.0;
    if (!mako._testMode) {
      obd.readPID(PID_INTAKE_MAP,intakeKpa);
      obd.readPID(PID_BAROMETRIC,atmosKpa);
      boostPsi = (intakeKpa - atmosKpa) * 0.145;
    }
    mako.drawBoostNeedle(boostPsi,true);
  }
  else if (currentGaugeType == 1) {
    int kph = 0;
    int mph = 0;
    if (!mako._testMode) {
      obd.readPID(PID_SPEED,kph);
      mph = kph * 0.621;
    }
    mako.drawMphNeedle(mph,true);
  }
  else if (currentGaugeType == 2) {
    int rpm = 0;
    if (!mako._testMode) {
      obd.readPID(PID_RPM,rpm);
    }
    mako.drawRpmNeedle(rpm,true);
  }
  else if (currentGaugeType == 3) {
    int throttlePerc = 0;
    if (!mako._testMode) {
      obd.readPID(PID_RELATIVE_THROTTLE_POS,throttlePerc);
    }
    mako.drawThrottleNeedle(throttlePerc,true);
  }

  mako.readTouchInput();
}
