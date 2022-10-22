/**
 * @file Screen_lcd.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief 16x2 lcd Screen
 * @date 2022-08
 */
#include "Screen_lcd.h"

/**
 * @brief constructor
 */
#if defined LCD_SCREEN
Screen_lcd::Screen_lcd()
: m_display(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE)
{}

/**
 * @brief display start screen
 */
void Screen_lcd::display_start()
{
  m_display.begin(16, 2);
  m_display.clear();
  m_display.setCursor(0, 0);
  m_display.print("pH/EC meter");
  m_display.setCursor(0, 1);
  m_display.print("Inzynier Domu");
}

/**
 * @brief display calibration mode screen
 */
void Screen_lcd::calibration_mode()
{
  m_display.clear();
  m_display.setCursor(0, 0);
  m_display.print("CALIB MODE");
}

/**
 * @brief display save point screen
 */
void Screen_lcd::save_data()
{
  m_display.clear();
  m_display.setCursor(0, 0);
  m_display.print("POINT SAVED");
}

/**
 * @brief display ph measurments screen
 */
void Screen_lcd::measurements_ph(const float temperature, const float ph)
{
  m_display.clear();
  m_display.setCursor(0, 0);
  m_display.print(ph);
  m_display.print("pH");

  // TODO: print temperature move to other function
  m_display.setCursor(0, 1);
  m_display.print(temperature);
  m_display.print((char)223);
  m_display.print("C");
}

/**
 * @brief display ec measurments screen
 */
void Screen_lcd::measurements_ec(const float temperature, const float ec)
{
  m_display.clear();
  m_display.setCursor(0, 0);
  m_display.print(ec);
  m_display.print("ms/cm");
  m_display.setCursor(0, 1);
  m_display.print(temperature);
  m_display.print((char)223);
  m_display.print("C");
}

/**
 * @brief display caloibration ph screen
 */
void Screen_lcd::calibration_ph(const uint8_t sample, const float temperature)
{
  long loop_time = millis();
  static long time;
  static bool toggle;

  m_display.clear();
  m_display.setCursor(0, 0);

  if (loop_time - time > Config::blink_time_calibration)
  {
    time = millis();
    toggle = !toggle;
  }

  if (toggle)
  {
    m_display.print(sample);
  }
  else
  {
    m_display.print(" ");
  }

  m_display.print(".0 pH");
}

/**
 * @brief display caloibration ec screen
 */
void Screen_lcd::calibration_ec(const double sample, uint8_t position, const float temperature)
{
  long loop_time = millis();
  static long time;
  static bool toggle;

  m_display.clear();
  m_display.setCursor(0, 0);

  if (loop_time - time > Config::blink_time_calibration)
  {
    time = millis();
    toggle = !toggle;
  }

  // TODO: better naming
  String text = String(sample, 3);
  if (toggle)
  {
    m_display.print(text);
  }
  else
  {
    if (position > 0)
    {
      position++;
    }
    if (text.length() > 5)
    {
      position++;
    }
    text[position] = ' ';
    m_display.print(text);
  }
  m_display.print("ms/cm");
}
#endif