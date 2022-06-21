/**
 * @file Linear_function.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief linear function y = ax + b structure
 * @date 2022-06
 */
#pragma once

#include <stdint.h>

///< Point structure
struct Point
{
  /**
   * @brief Construct a new Point object
   * @param _y: y value
   * @param _x: x value
   */
  Point(double _y = 0, double _x = 0)
  : y(_y)
  , x(_x){};
  double y;
  double x;
};

class Linear_function
{
  public:
  Linear_function(const Point points[2]={});
  void set_points(const Point points[2]);
  double find_y(uint16_t x);

  private:
  double a; ///< slope
  double b; ///< shift
};