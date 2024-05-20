#include "GameManager.hpp"

GameManager::GameManager() {
  std::cout << "Game Manager initialized." << std::endl;
}

GameManager::~GameManager() {
  std::cout << "Game Manager deconstructed" << std::endl;
  player1_ptr = nullptr;
  player2_ptr = nullptr;
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

    std::shared_ptr<Player> new_player_ptr {new Player(name, piece_char)};
    new_player_ptr->DisplayPlayerInfo();

    if (playerCount == 1) {
      player1_ptr = new_player_ptr;
    } else {
      player2_ptr = new_player_ptr;
    }
    
    playerCount++;
    new_player_ptr = nullptr;
  }

  return true;
}

bool GameManager::GetIsGameComplete() {
  return isGameComplete;
}