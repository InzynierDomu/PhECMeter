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
: m_display(Config::screen_width, Config::screen_height, &Wire)
{
  m_display.begin(SSD1306_SWITCHCAPVCC, Config::screen_address);
  m_display.clearDisplay();
  m_display.setRotation(2);
  m_display.setTextSize(2);
  m_display.setTextColor(SSD1306_WHITE);
  m_display.display();
}

/**
 * @brief display start screen
 */
void Screen_oled::display_start()
{
  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.setTextSize(1);
  m_display.println("pH/EC meter");
  m_display.println("Inzynier Domu");
  m_display.display();
  m_display.setTextSize(2);
}

/**
 * @brief display calibration mode screen
 */
void Screen_oled::display_calib_mode()
{
  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.println("CALIB");
  m_display.println("MODE");
  m_display.display();
}

/**
 * @brief display save point screen
 */
void Screen_oled::display_save_data()
{
  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.println("POINT");
  m_display.println("SAVED");
  m_display.display();
}

/**
 * @brief display ph measurments screen
 */
void Screen_oled::display_ph(const float temperature, const float ph)
{
  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.print(temperature);
  m_display.print((char)247);
  m_display.println("C");
  m_display.print(ph);
  m_display.print("pH");
  m_display.display();
}

/**
 * @brief display ec measurments screen
 */
void Screen_oled::display_ec(const float temperature, const float ec)
{
  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.print(temperature);
  m_display.print((char)247);
  m_display.println("C");
  m_display.print(ec);
  m_display.print("ms/cm");
  m_display.display();
}

/**
 * @brief display caloibration ph screen
 */
void Screen_oled::display_calibration_ph(const uint8_t sample, const float temperature)
{
  long loop_time = millis();
  static long time;
  static bool toggle;

  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.print(temperature);
  m_display.print((char)247);
  m_display.println("C");

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
  m_display.display();
}

/**
 * @brief display caloibration ec screen
 */
void Screen_oled::display_calibration_ec(const double sample, uint8_t position, const float temperature)
{
  long loop_time = millis();
  static long time;
  static bool toggle;

  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.print(temperature);
  m_display.print((char)247);
  m_display.println("C");

  if (loop_time - time > Config::blink_time_calibration)
  {
    time = millis();
    toggle = !toggle;
  }

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

  m_display.display();
}
#endif