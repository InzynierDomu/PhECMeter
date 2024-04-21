/**
 * @file Linear_function.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief linear function y = ax + b structure
 * @date 2022-06
 */
#pragma once

#include <stdint.h>

/// @brief Point structure
struct Point
{
  /**
   * @brief Construct a new Point object
   * @param _analog_val: analog_val value directly from the converter
   * @param _unit_val: unit_val value in SI unit
   */
  Point(double _analog_val = 0, double _unit_val = 0)
  : unit_val(_unit_val)
  , analog_val(_analog_val){};
  double unit_val;
  double analog_val;
};

/// @brief liner function store and calculate
class Linear_function
{
  public:
  Linear_function(const Point points[2] = {});
  void set_points(const Point points[2]);
  double find_unit_val(uint16_t analog_val);

  private:
  double slope;
  double shift;
};