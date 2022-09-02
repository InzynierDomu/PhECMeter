/**
 * @file IScreen.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief Screens interface
 * @date 2022-08
 */
#pragma once

#include <Wire.h>

class IScreen
{
  public:
  ~IScreen() {}
  virtual void display_start() = 0;
  virtual void display_calib_mode() = 0;
  virtual void display_save_data() = 0;
  virtual void display_ph(const float temperature, const float ph) = 0;
  virtual void display_ec(const float temperature, const float ec) = 0;
  virtual void display_calibration_ph(const uint8_t sample, const float temperature) = 0;
  virtual void display_calibration_ec(const double sample, uint8_t position, const float temperature) = 0;
};