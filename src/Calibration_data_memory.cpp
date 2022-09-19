/**
 * @file Linear_function.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief saving and loading calibration data from memory
 * @date 2022-06
 */
#include "Calibration_data_memory.h"

enum memory_map
{
  ph_calibration = 0,
  ec_calibration = 4,
  ph_max = 8,
  ec_max = 9
};

/**
 * @brief save ph calibration data
 * @param points calibration data
 */
void Calibration_data_memory::save_ph_calibration(const Point points[2])
{
  save_calibration(points, memory_map::ph_calibration);
}

/**
 * @brief save ec calibration data
 * @param points calibration data
 */
void Calibration_data_memory::save_ec_calibration(const Point points[2])
{
  save_calibration(points, memory_map::ec_calibration);
}

/**
 * @brief save ph max value for automation
 * @param value ph value
 */
void Calibration_data_memory::save_ph_max(const double value)
{
  EEPROM.put<double>(sizeof(double) * memory_map::ph_max, value);
}

/**
 * @brief save ec max value for automation
 * @param value ec value
 */
void Calibration_data_memory::save_ec_max(const double value)
{
  EEPROM.put<double>(sizeof(double) * memory_map::ec_max, value);
}

/**
 * @brief load ph calibration data
 * @param points calibration data to fill
 */
void Calibration_data_memory::load_ph_calibration(Point points[2])
{
  load_calibration(points, memory_map::ph_calibration);
}

/**
 * @brief load ec calibration data
 * @param points calibration data to fill
 */
void Calibration_data_memory::load_ec_calibration(Point points[2])
{
  load_calibration(points, memory_map::ec_calibration);
}

/**
 * @brief load ph max value for automation
 * @return max ph value
 */
double Calibration_data_memory::load_ph_max()
{
  double max_ph;
  EEPROM.get<double>(sizeof(double) * memory_map::ph_max, max_ph);
  return max_ph;
}

/**
 * @brief load ec max value for automation
 * @return max ec value
 */
double Calibration_data_memory::load_ec_max()
{
  double max_ec;
  EEPROM.get<double>(sizeof(double) * memory_map::ec_max, max_ec);
  return max_ec;
}

void Calibration_data_memory::save_calibration(const Point points[2], const uint8_t start)
{
  EEPROM.put<double>(sizeof(double) * start, points[0].x);
  EEPROM.put<double>(sizeof(double) * (start + 1), points[0].y);
  EEPROM.put<double>(sizeof(double) * (start + 2), points[1].x);
  EEPROM.put<double>(sizeof(double) * (start + 3), points[1].y);
}

void Calibration_data_memory::load_calibration(Point points[2], const uint8_t start)
{
  double read_value_x;
  double read_value_y;
  EEPROM.get<double>(sizeof(double) * start, read_value_x);
  EEPROM.get<double>(sizeof(double) * (start + 1), read_value_y);
  points[0] = Point(read_value_x, read_value_y);
  EEPROM.get<double>(sizeof(double) * (start + 2), read_value_x);
  EEPROM.get<double>(sizeof(double) * (start + 3), read_value_y);
  points[1] = Point(read_value_x, read_value_y);
}