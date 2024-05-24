#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <ostream>


struct coordinates{
    int x;
    int y;
  };
  
std::ostream &operator<<(std::ostream &os, const coordinates &rhs);

#endif