/**
 * @file Linear_function.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief saving and loading calibration data from memory
 * @date 2022-06
 */
#include "Calibration_data_memory.h"

/**
 * @brief save ph calibration data
 * @param points calibration data
 */
void Calibration_data_memory::save_ph_calibration(const Point points[2])
{
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 0, points[0].x);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 1, points[0].y);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 2, points[1].x);
  EEPROM.put<uint16_t>(sizeof(uint16_t) * 3, points[1].y);
}

/**
 * @brief save ec calibration data
 * @param points calibration data
 */
void Calibration_data_memory::save_ec_calibration(const Point points[2]) {}

/**
 * @brief load ph calibration data
 * @param points calibration data to fill
 */
void Calibration_data_memory::load_ph_calibration(Point points[2])
{
  uint16_t read_value_x;
  uint16_t read_value_y;
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 0, read_value_x);
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 1, read_value_y);
  points[0] = Point(read_value_x, read_value_y);
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 2, read_value_x);
  EEPROM.get<uint16_t>(sizeof(uint16_t) * 3, read_value_y);
  points[1] = Point(read_value_x, read_value_y);
}

/**
 * @brief load ec calibration data
 * @param points calibration data to fill
 */
void Calibration_data_memory::load_ec_calibration(Point points[2]) {}