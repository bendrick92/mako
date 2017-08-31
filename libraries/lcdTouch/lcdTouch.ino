#include <Arduino.h>
#include <SPI.h>
#include <MultiLCD.h>
#include "touch.h"

LCD_R61581 lcd;


void setup(){
  lcd.begin();
  lcd.setFontSize(FONT_SIZE_MEDIUM);  //set font size
  lcd.setColor(RGB16_YELLOW);  //set strings color
  lcd.println("DFRobot");
  lcd.println("TELEMATICS LCD SHIELD V1.0");
  lcd.println();
  lcd.setColor(RGB16_WHITE);
  
  touch.init();
}

void loop(){
  lcd.setCursor(0, 8);
  int x, y;
  if ( touch.read(x, y) ){
    lcd.print("X:");
    lcd.print(x);
    lcd.print(" Y:");
    lcd.print(y);
    lcd.print("  ");
  } else {
    lcd.print("           ");
  }
}
