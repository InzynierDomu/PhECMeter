#include "Linear_function.h"

Linear_function::Linear_function() {}

Linear_function::Linear_function(Point first, Point second)
{
  set_points(first, second);
}

double Linear_function::find_y(int x)
{
  return (a * x + b);
}

void Linear_function::set_points(Point first, Point second)
{
  a = (second.y - first.y) / (double)(second.x - first.x);
  b = first.y - (a * first.x);
}

void Linear_function::set_points(std::pair<Point, Point> points)
{
  a = (points.second.y - points.first.y) / (double)(points.second.x - points.first.x);
  b = points.first.y - (a * points.first.x);
}
