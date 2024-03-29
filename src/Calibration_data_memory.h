/**
 * @file Linear_function.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief saving and loading calibration data from memory
 * @date 2022-06
 */
#pragma once

#include "Linear_function.h"

#include <EEPROM.h>

/// @brief saving and reading calibration from sd card
class Calibration_data_memory
{
  public:
  void save_ph_calibration(const Point points[2]);
  void save_ec_calibration(const Point points[2]);
  void load_ph_calibration(Point points[2]);
  void load_ec_calibration(Point points[2]);

  private:
  void save_calibration(const Point points[2], const uint8_t start);
  void load_calibration(Point points[2], const uint8_t start);
};