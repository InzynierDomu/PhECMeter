/**
 * @file Screen_lcd.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief OLED Screen
 * @date 2022-08
 */
#include "Screen_oled.h"
#ifndef LCD_SCREEN

/**
 * @brief constructor
 */
Screen_oled::Screen_oled()
{
  ssd1306_128x32_i2c_init();
  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_flipHorizontal();
  ssd1306_flipVertical();
}

/**
 * @brief display start screen
 */
void Screen_oled::display_start()
{
  ssd1306_clearScreen();
  ssd1306_charF6x8(0, 0, "pH/EC meter");
  ssd1306_charF6x8(0, 1, "Inzynier Domu");
}

/**
 * @brief display calibration mode screen
 */
void Screen_oled::display_calib_mode()
{
  ssd1306_clearScreen();
  ssd1306_charF12x16(0, 0, "CALIB", STYLE_NORMAL);
  ssd1306_charF12x16(0, 2, "MODE", STYLE_NORMAL);
}

/**
 * @brief display save point screen
 */
void Screen_oled::display_save_data()
{
  ssd1306_clearScreen();
  ssd1306_charF12x16(0, 0, "POINT", STYLE_NORMAL);
  ssd1306_charF12x16(0, 2, "SAVED", STYLE_NORMAL);
}

/**
 * @brief display ph measurments screen
 */
void Screen_oled::display_ph(const float temperature, const float ph)
{
  ssd1306_clearScreen();
  char buf[10];
  String text = String(temperature) + "'C";
  text.toCharArray(buf, 10);
  ssd1306_charF12x16(0, 0, buf, STYLE_NORMAL);
  text = String(ph) + "pH";
  text.toCharArray(buf, 10);
  ssd1306_charF12x16(0, 2, buf, STYLE_NORMAL);
}

/**
 * @brief display ec measurments screen
 */
void Screen_oled::display_ec(const float temperature, const float ec)
{
  ssd1306_clearScreen();
  char buf[10];
  String text = String(temperature) + "'C";
  text.toCharArray(buf, 10);
  ssd1306_charF12x16(0, 0, buf, STYLE_NORMAL);
  text = String(ec) + "ms/cm";
  text.toCharArray(buf, 10);
  ssd1306_charF12x16(0, 2, buf, STYLE_NORMAL);
}

/**
 * @brief display caloibration ph screen
 */
void Screen_oled::display_calibration_ph(const uint8_t sample, const float temperature)
{
  long loop_time = millis();
  static long time;
  static bool toggle;

  ssd1306_clearScreen();
  char buf[10];
  String text = String(temperature) + "'C";
  text.toCharArray(buf, 10);
  ssd1306_charF12x16(0, 0, buf, STYLE_NORMAL);

  if (loop_time - time > Config::blink_time_calibration)
  {
    time = millis();
    toggle = !toggle;
  }

  if (toggle)
  {
    text = String(sample);
  }
  else
  {
    text = String(" ");
  }

  text += ".0 pH";
  text.toCharArray(buf, 10);
  ssd1306_charF12x16(0, 2, buf, STYLE_NORMAL);
}

/**
 * @brief display caloibration ec screen
 */
void Screen_oled::display_calibration_ec(const double sample, uint8_t position, const float temperature)
{
  long loop_time = millis();
  static long time;
  static bool toggle;

  ssd1306_clearScreen();
  char buf[10];
  String text = String(temperature) + "'C";
  text.toCharArray(buf, 10);
  ssd1306_charF12x16(0, 0, buf, STYLE_NORMAL);

  if (loop_time - time > Config::blink_time_calibration)
  {
    time = millis();
    toggle = !toggle;
  }

  text = String(sample, 3);
  if (toggle)
  {
    text.toCharArray(buf, 8);
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
  }
  text += "ms/cm";
  text.toCharArray(buf, 10);
  ssd1306_charF12x16(0, 2, buf, STYLE_NORMAL);
}
#endif