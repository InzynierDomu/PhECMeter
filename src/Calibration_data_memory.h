#ifndef CALIBRATION_DATA_MEMORY
#define CALIBRATION_DATA_MEMORY

#include <EEPROM.h>
#include <ArduinoSTL.h>

#include "Linear_function.h"

class Calibration_data_memory
{
public:  
  Calibration_data_memory();
  void save_ph_calibration(std::pair<Point, Point> points);
  void save_ec_calibration(std::pair<Point, Point> points);
  std::pair<Point, Point> load_ph_calibration();
  std::pair<Point, Point> load_ec_calibration();
};

#endif //CALIBRATION_DATA_MEMORY