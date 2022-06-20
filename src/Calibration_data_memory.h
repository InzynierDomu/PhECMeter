#pragma once

#include "Linear_function.h"

#include <EEPROM.h>

class Calibration_data_memory
{
  public:
  Calibration_data_memory();
  void save_ph_calibration(Point points[2]);
  void save_ec_calibration(Point points[2]);
  void load_ph_calibration(Point points[2]);
  void load_ec_calibration(Point points[2]);
};