#include "Calibration_data_memory.h"

Calibration_data_memory::Calibration_data_memory()
{}

void Calibration_data_memory::save_ph_calibration(std::pair<Point, Point> points)
{}

void Calibration_data_memory::save_ec_calibration(std::pair<Point, Point> points)
{}

std::pair<Point, Point> Calibration_data_memory::load_ph_calibration()
{
  // const uint16_t read_value_x;
  // const uint16_t read_value_y;
  // EEPROM.get<uint16_t>(0,read_value_x);
  // EEPROM.get<uint16_t>(4,read_value_y);
  // Point first_sample(read_value_x, read_value_y);
  // EEPROM.get<uint16_t>(8,read_value_x);
  // EEPROM.get<uint16_t>(12,read_value_y);
  // Point second_sample(read_value_x, read_value_y);
}

std::pair<Point, Point> Calibration_data_memory::load_ec_calibration()
{}