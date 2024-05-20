#include "Player.hpp"
/* [Notes]
 * 
 * C++ usually makes shallow copies
 * When no copy constructor is initialized, C++ will generate one
 * 
 * */

Player::Player(std::string name_val, char piece_char)
    :_name{name_val}, _piece{piece_char} {
        std::cout << "Player " << _name << " initialized with char " << _piece << std::endl;
    }
Player::~Player() { std::cout << "Player " << _name << " deconstructed" << std::endl; }