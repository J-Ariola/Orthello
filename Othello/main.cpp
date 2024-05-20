#include "GameManager.hpp"
#include <iostream>

int main () {
  std::cout <<"Welcome to Othello" << std::endl;
  GameManager* gm_ptr = new GameManager();
  
  return 0;
}