#include "GameManager.hpp"
#include <iostream>

int main () {
  std::cout << std::boolalpha;
  std::cout << "Welcome to Othello" << std::endl;
  GameManager* gm_ptr = new GameManager();

  if (!(gm_ptr -> StartGame())) {
    std::cerr << "Game did not start successfully." << std::endl;
    return 1;
  }

  delete gm_ptr;
  return 0;
}