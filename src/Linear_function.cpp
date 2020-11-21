#include "Linear_function.h"

Linear_function::Linear_function()
{}

Linear_function::Linear_function(Point first, Point second)
{
    set_points(first, second);
}

double Linear_function::find_y(int x)
{
  return(a * x + b);
}

void Linear_function::set_points(Point first, Point second)
{
  a = (second.y - first.y)/(double)(second.x - first.x);
  b = first.y - (a * first.x);
}
