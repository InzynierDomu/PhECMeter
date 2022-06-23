/**
 * @file Data_presentation.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief send data via serial and present on screen
 * @date 2022-06
 */
#pragma once

#include "Adafruit_BusIO_Register.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class Data_presentation
{
  public:
  Data_presentation();
  void display_start();
  void display_calib_mode();
  void display_save_data();
  void presentation_measurements_ph(const float temperature, const float ph);
  void presentation_measurements_ec(const float temperature, const float ec);
  void display_calibration_ph(const uint8_t sample, const float temperature);
  void display_calibration_ec(const double sample, uint8_t position, const float temperature);

  private:
  Adafruit_SSD1306 m_display; ///< ssd1306 oled screen
};