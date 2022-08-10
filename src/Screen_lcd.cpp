#include "Screen_lcd.h"

#ifdef LCD_SCREEN
Screen_lcd::Screen_lcd()
: m_display(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
{
  m_display.begin(16, 2);
  m_display.clear();
}
#endif