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
  save_calibration(points, 0);
}

/**
 * @brief save ec calibration data
 * @param points calibration data
 */
void Calibration_data_memory::save_ec_calibration(const Point points[2])
{
  save_calibration(points, 4);
}

/**
 * @brief load ph calibration data
 * @param points calibration data to fill
 */
void Calibration_data_memory::load_ph_calibration(Point points[2])
{
  load_calibration(points, 0);
}

/**
 * @brief load ec calibration data
 * @param points calibration data to fill
 */
void Calibration_data_memory::load_ec_calibration(Point points[2])
{
  load_calibration(points, 4);
}

void Calibration_data_memory::save_calibration(const Point points[2], const uint8_t start)
{
  EEPROM.put<double>(sizeof(double) * start, points[0].x);
  EEPROM.put<double>(sizeof(double) * start + 1, points[0].y);
  EEPROM.put<double>(sizeof(double) * start + 2, points[1].x);
  EEPROM.put<double>(sizeof(double) * start + 3, points[1].y);
}

void Calibration_data_memory::load_calibration(Point points[2], const uint8_t start)
{
  double read_value_x;
  double read_value_y;
  EEPROM.get<double>(sizeof(double) * start, read_value_x);
  EEPROM.get<double>(sizeof(double) * start + 1, read_value_y);
  points[0] = Point(read_value_x, read_value_y);
  EEPROM.get<double>(sizeof(double) * start + 2, read_value_x);
  EEPROM.get<double>(sizeof(double) * start + 3, read_value_y);
  points[1] = Point(read_value_x, read_value_y);
}