#include "Calibration_data_memory.h"

Calibration_data_memory::Calibration_data_memory() {}

void Calibration_data_memory::save_ph_calibration(Point points[2])
{
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 0, points[0].x);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 1, points[0].y);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 2, points[1].x);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 3, points[1].y);
}

void Calibration_data_memory::save_ec_calibration(Point points[2]) {}

void Calibration_data_memory::load_ph_calibration(Point points[2])
{
  uint16_t read_value_x;
  uint16_t read_value_y;
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 0, read_value_x);
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 1, read_value_y);
  Point first_sample(read_value_x, read_value_y);
  points[0] = first_sample;
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 2, read_value_x);
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 3, read_value_y);
  Point second_sample(read_value_x, read_value_y);
  points[1] = second_sample;
}

void Calibration_data_memory::load_ec_calibration(Point points[2]) {}