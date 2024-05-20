#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

class Player {
  public:
    Player(std::string name_val = "None", char piece_char = '0');
    ~Player();
    std::string DisplayPlayerInfo() {
      return "player name: " + _name + "\npiece char" + _piece;
    }


    private:
      std::string _name;
      char _piece;
};

#endif // PLAYER_HPP