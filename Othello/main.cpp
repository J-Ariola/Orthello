#include "GameManager.hpp"
#include <iostream>
#include <memory>

int main () {
  std::cout << std::boolalpha;
  std::cout << "Welcome to Othello" << std::endl;
  std::unique_ptr<GameManager> gm_ptr {new GameManager()};

  if (!(gm_ptr-> StartGame())) {
    std::cerr << "Game did not start successfully." << std::endl;
    gm_ptr = nullptr;
    return 1;
  }

  gm_ptr->Update();

  // gm_ptr->PrintGameboard();

  gm_ptr = nullptr;
  return 0;
}