#pragma once

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
  Linear_function(Point points[2]);
  void set_points(Point points[2]);
  double find_y(int x);

  private:
  // y = ax + b
  double a;
  double b;
};