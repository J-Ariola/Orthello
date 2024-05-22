#ifndef BOARD_COORDINATE_UTILS_CPP
#define BOARD_COORDINATE_UTILS_CPP

#include <string>
#include <iostream>
#include <map>
#include <cctype>
#include <vector>


namespace BoardCoordinateUtils {
  
  const std::map<char, int> char_to_int_map = {
    {'A', 0},
    {'B', 1},
    {'C', 2},
    {'D', 3},
    {'E', 4},
    {'F', 5},
    {'G', 6},
    {'H', 7},
  };

  struct coordinates{
    int x;
    int y;
  public: 
    std::ostream &operator<<(std::ostream &os) {
      os << "[" << x << ", " << y << "]";
      return os;
    }
  };

  bool static inline IsValidCoordinates (const std::string &placement_coordinates_string) {
    if ( placement_coordinates_string.length() != 2 || 
    !std::isalpha(placement_coordinates_string.at(0)) || 
    !std::isdigit(placement_coordinates_string.at(1)) ) {
      return false;
    }
    return true;
  };

  char static inline IndexToGridChar (const int &val) {
    for (auto &i : char_to_int_map) {
      if (i.second == val)
        return i.first;
    }
    return 'Z';
  };

  coordinates static inline StringCoordinatesToArrayIndeces (const std::string &placement_coordinates_string) {
    std::cout << "Placement Coordinates " << placement_coordinates_string.at(0) << " " << placement_coordinates_string.at(1) << std::endl;
    int x_val = placement_coordinates_string.at(1) - '1'; // Counters ASCII
    int y_val = std::toupper(char_to_int_map.at(placement_coordinates_string.at(0)));
    coordinates resultCoords;

    resultCoords.x = x_val;
    resultCoords.y = y_val;
    return resultCoords;
  };
  
};


#endif