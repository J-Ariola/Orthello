#ifndef BOARD_COORDINATE_UTILS_CPP
#define BOARD_COORDINATE_UTILS_CPP

#include <string>
#include <iostream>
#include <map>

namespace BoardCoordinateUtils {

  const std::map<char, int> string_to_int_map = {
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
  };

  coordinates static inline StringCoordinatesToArrayIndeces (const std::string &placement_coordinates) {
    std::cout << "Placement Coordinates " << placement_coordinates.at(0) << " " << placement_coordinates.at(1) << std::endl;
    int x_val = placement_coordinates.at(1) - '1'; // Counters ASCII
    int y_val = string_to_int_map.at(placement_coordinates.at(0));
    coordinates resultCoords;

    resultCoords.x = x_val;
    resultCoords.y = y_val;
    return resultCoords;
  };
};


#endif