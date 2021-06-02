#ifndef LINEAR_FUNCTION
#define LINEAR_FUNCTION

struct Point
{
  Point(int _y = 0, int _x = 0):y(_y), x(_x){};
  int y;
  int x;
};

class Linear_function
{
public:
  Linear_function();
  Linear_function(Point first, Point second);
  void set_points(Point first, Point second);
  void set_points(Point* points);
  double find_y(int x);

private:
  //y = ax + b
  double a;
  double b;
};

#endif //LINEAR_FUNCTION