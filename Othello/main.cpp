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

  while (!gm_ptr->GetIsGameComplete()){
    gm_ptr->Update();
  }

  gm_ptr = nullptr;
  std::cout << "REACHED END OF PROGRAM SAFELY" << std::endl;
  return 0;
}