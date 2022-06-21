/**
 * @file Linear_function.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief saving and loading calibration data from memory
 * @date 2022-06
 */
#pragma once

#include "Linear_function.h"

#include <EEPROM.h>

class Calibration_data_memory
{
  public:
  void save_ph_calibration(const Point points[2]);
  void save_ec_calibration(const Point points[2]);
  void load_ph_calibration(Point points[2]);
  void load_ec_calibration(Point points[2]);
};