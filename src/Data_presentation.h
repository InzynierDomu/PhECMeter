/**
 * @file Data_presentation.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief send data via serial and present on screen
 * @date 2022-06
 */
#pragma once

#include "Linear_function.h"
#include "Screen_lcd.h"
#include "Screen_oled.h"

#include <stdint.h>

/// @brief Presentation data on screen and serial
class Data_presentation
{
  public:
  Data_presentation();
  void init();
  void calibration_mode();
  void save_data();
  void measurements_ph(const float temperature, const float ph);
  void measurements_ec(const float temperature, const float ec);
  void calibration_ph(const uint8_t sample, const float temperature, const float origin);
  void calibration_ec(const double sample, uint8_t position, const float temperature, const float origin);
  void print_ph_calibration(Point points[2]);
  void print_ec_calibration(Point points[2]);

  private:
  void print_points(Point points[2]);
#if defined LCD_SCREEN
  Screen_lcd m_display; ///< lcd screen
#else
  Screen_oled m_display; ///< oled screen
#endif
};