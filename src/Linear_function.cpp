#include "Linear_function.h"

/**
 * @brief Construct a new Linear_function::Linear_function object
 * @param points: points to calculate linear function
 */
Linear_function::Linear_function(const Point points[2])
: a(1)
, b(0)
{
  set_points(points);
}

/**
 * @brief find point on linear function
 * @param x: input variable to function
 * @return double: return value from function
 */
double Linear_function::find_y(uint16_t x)
{
  return (a * x + b);
}

/**
 * @brief set points to calculate linear function
 * @param points: points to set
 */
void Linear_function::set_points(const Point points[2])
{
  a = (points[1].y - points[0].y) / (points[1].x - points[0].x);
  b = points[0].y - (a * points[0].x);
}
