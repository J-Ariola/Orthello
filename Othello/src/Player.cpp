#include "Player.hpp"
/* [Notes]
 * 
 * C++ usually makes shallow copies
 * When no copy constructor is initialized, C++ will generate one
 * 
 * */

Player::Player(std::string name_val, char piece_char)
    :_name{name_val}, _piece{piece_char} { }
Player::~Player() {}

char Player::GetPiece() { return _piece; }
std::string Player::GetName() { return _name; }