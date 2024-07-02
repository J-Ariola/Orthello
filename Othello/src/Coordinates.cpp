#include "Coordinates.hpp"

std::ostream &operator<<(std::ostream &os, const coordinates &rhs) {
  os << "[" << rhs.x << ", " << rhs.y << "]";
  return os;
}
