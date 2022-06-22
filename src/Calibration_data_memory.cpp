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
  EEPROM.put<double>(sizeof(double) * 0, points[0].x);
  EEPROM.put<double>(sizeof(double) * 1, points[0].y);
  EEPROM.put<double>(sizeof(double) * 2, points[1].x);
  EEPROM.put<double>(sizeof(double) * 3, points[1].y);
}

/**
 * @brief save ec calibration data
 * @param points calibration data
 */
void Calibration_data_memory::save_ec_calibration(const Point points[2])
{
  EEPROM.put<double>(sizeof(double) * 4, points[0].x);
  EEPROM.put<double>(sizeof(double) * 5, points[0].y);
  EEPROM.put<double>(sizeof(double) * 6, points[1].x);
  EEPROM.put<double>(sizeof(double) * 7, points[1].y);
}

/**
 * @brief load ph calibration data
 * @param points calibration data to fill
 */
void Calibration_data_memory::load_ph_calibration(Point points[2])
{
  double read_value_x;
  double read_value_y;
  EEPROM.get<double>(sizeof(double) * 0, read_value_x);
  EEPROM.get<double>(sizeof(double) * 1, read_value_y);
  points[0] = Point(read_value_x, read_value_y);
  EEPROM.get<double>(sizeof(double) * 2, read_value_x);
  EEPROM.get<double>(sizeof(double) * 3, read_value_y);
  points[1] = Point(read_value_x, read_value_y);
}

/**
 * @brief load ec calibration data
 * @param points calibration data to fill
 */
void Calibration_data_memory::load_ec_calibration(Point points[2])
{
  double read_value_x;
  double read_value_y;
  EEPROM.get<double>(sizeof(double) * 4, read_value_x);
  EEPROM.get<double>(sizeof(double) * 5, read_value_y);
  points[0] = Point(read_value_x, read_value_y);
  EEPROM.get<double>(sizeof(double) * 6, read_value_x);
  EEPROM.get<double>(sizeof(double) * 7, read_value_y);
  points[1] = Point(read_value_x, read_value_y);
}