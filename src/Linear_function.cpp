#include "Linear_function.h"

/**
 * @brief Construct a new Linear_function::Linear_function object
 * @param points: points to calculate linear function
 */
Linear_function::Linear_function(const Point points[2])
: slope(1)
, shift(0)
{
  set_points(points);
}

/**
 * @brief find point on linear function
 * @param x: input variable to function
 * @return double: return value from function
 */
double Linear_function::find_unit_val(uint16_t analog_val)
{
  return (slope * analog_val + shift);
}

/**
 * @brief set points to calculate linear function
 * @param points: points to set
 */
void Linear_function::set_points(const Point points[2])
{
  slope = (points[1].unit_val - points[0].unit_val) / (points[1].analog_val - points[0].analog_val);
  shift = points[0].unit_val - (slope * points[0].analog_val);
}
