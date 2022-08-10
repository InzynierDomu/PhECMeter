#pragma once
#ifdef LCD_SCREEN

#include "Config.h"
#include "LiquidCrystal_I2C.h"
#include "Screen.h"

class Screen_lcd : public Screen
{
  public:
  Screen_lcd(/* args */);

  private:
  LiquidCrystal_I2C m_display; 
}
#endif