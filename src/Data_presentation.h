/**
 * @file Data_presentation.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief send data via serial and present on screen
 * @date 2022-06
 */
#pragma once

#include <stdint.h>
#include "Screen_lcd.h"
#include "Screen_oled.h"
#include "Linear_function.h"

class Data_presentation
{
  public:
  Data_presentation();
  void init();
  void display_calib_mode();
  void display_save_data();
  void presentation_measurements_ph(const float temperature, const float ph);
  void presentation_measurements_ec(const float temperature, const float ec);
  void display_calibration_ph(const uint8_t sample, const float temperature);
  void display_calibration_ec(const double sample, uint8_t position, const float temperature);
  void print_ph_calibration(Point points[2]);
  void print_ec_calibration(Point points[2]);

  private:
#if defined LCD_SCREEN
  Screen_lcd m_display; ///< lcd screen
#else
  Screen_oled m_display; ///< oled screen
#endif
};