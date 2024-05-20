#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
  public:
    Player(std::string name_val = "None", char piece_char = '0');
    ~Player();

    private:
      std::string _name;
      char _piece;
};

#endif // PLAYER_HPP