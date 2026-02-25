template <class T> 
T Point<T>::farthest() const {
  T absx = x > 0 ? x : -x;
  T absy = y > 0 ? y : -y;
  return absx < absy ? absy : absx;
}

template <class T>
Point<T>::Point() : x {}, y {} {}

template <class T> 
Point<T>::Point(T x, T y) : x { x }, y { y } {}

template <class T>
T Point<T>::get_x() const {
  return x;
}

template <class T>
T Point<T>::get_y() const {
  return y;
}

template <class T>
void Point<T>::set_x(T x) {
  this->x = x;
}

template <class T>
void Point<T>::set_y(T y) {
  this->y = y;
}

template <class T>
bool Point<T>::within_square(T d) const {
  return 2 * farthest() <= d;
}