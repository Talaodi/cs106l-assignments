template <class T>
class Point {
private:
  T x, y;

  T farthest() const;

public:
  Point(T x, T y);
  Point();

  T get_x() const;
  T get_y() const;
  void set_x(T x);
  void set_y(T y);
  bool within_square(T d) const;
};

#include "class.cpp"