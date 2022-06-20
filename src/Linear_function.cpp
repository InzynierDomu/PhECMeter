#include "Linear_function.h"

Linear_function::Linear_function() {}

Linear_function::Linear_function(Point points[2])
{
  set_points(points);
}

double Linear_function::find_y(int x)
{
  return (a * x + b);
}

void Linear_function::set_points(Point points[2])
{
  a = (points[1].y - points[0].y) / (double)(points[1].x - points[0].x);
  b = points[0].y - (a * points[0].x);
}
