#pragma once

#include <ArduinoSTL.h>

struct Point
{
  Point(double _y = 0, double _x = 0)
  : y(_y)
  , x(_x){};
  double y;
  double x;
};

class Linear_function
{
  public:
  Linear_function();
  Linear_function(Point first, Point second);
  void set_points(Point first, Point second);
  void set_points(std::pair<Point, Point> points);
  double find_y(int x);

  private:
  // y = ax + b
  double a;
  double b;
};