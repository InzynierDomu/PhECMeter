#pragma once
#ifndef LCD_SCREEN

#include "Adafruit_BusIO_Register.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Config.h"
#include "Screen.h"

class Screen_oled : public Screen
{
  public:
  Screen_oled();

  private:
  Adafruit_SSD1306 m_display; ///< ssd1306 oled screen
};
#endif