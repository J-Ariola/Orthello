#include "GameManager.hpp"

GameManager::GameManager() {
  std::cout << "Game Manager initialized." << std::endl;
}

GameManager::~GameManager() {
  std::cout << "Game Manager deconstructed" << std::endl;
  delete player1_ptr;
  delete player2_ptr;
}

bool GameManager::StartGame() {

  if (InitializePlayers()) return true;

  return false;
}

bool GameManager::InitializePlayers() {
  unsigned int playerCount {1};

  while (playerCount <= 2) {
    std::string name{""};
    char piece_char{};

    std::cout << "Please enter player " << playerCount << "\'s name: ";
    std::cin >> name;
    std::cout << std::endl;

    std::cout << "Welcome " << name << ", please enter a single character to represent your piece: ";
    std::cin >> piece_char;

    Player* p_ptr {new Player(name, piece_char)};
    p_ptr->DisplayPlayerInfo();

    if (playerCount == 1) {
      player1_ptr = p_ptr;
    } else {
      player2_ptr = p_ptr;
    }
    
    playerCount++;
    p_ptr = nullptr;
  }

  return true;
}

bool GameManager::GetIsGameComplete() {
  return isGameComplete;
}