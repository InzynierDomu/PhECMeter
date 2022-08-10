#include "Screen_oled.h"
#ifndef LCD_SCREEN

Screen_oled::Screen_oled()
: m_display(Config::screen_width, Config::screen_height, &Wire)
{
  m_display.begin(SSD1306_SWITCHCAPVCC, Config::screen_address);
  m_display.clearDisplay();
  m_display.setRotation(2);
  m_display.setTextSize(2);
  m_display.setTextColor(SSD1306_WHITE);
  m_display.display();
}
#endif