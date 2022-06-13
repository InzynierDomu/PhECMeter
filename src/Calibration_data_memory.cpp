#include "Calibration_data_memory.h"

Calibration_data_memory::Calibration_data_memory() {}

void Calibration_data_memory::save_ph_calibration(std::pair<Point, Point> points)
{
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 0, points.first.x);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 1, points.first.y);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 2, points.second.x);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 3, points.second.y);
}

void Calibration_data_memory::save_ec_calibration(std::pair<Point, Point> points) {}

std::pair<Point, Point> Calibration_data_memory::load_ph_calibration()
{
  uint16_t read_value_x;
  uint16_t read_value_y;
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 0, read_value_x);
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 1, read_value_y);
  Point first_sample(read_value_x, read_value_y);
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 2, read_value_x);
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 3, read_value_y);
  Point second_sample(read_value_x, read_value_y);

  return std::make_pair(first_sample, second_sample);
}

std::pair<Point, Point> Calibration_data_memory::load_ec_calibration() {}