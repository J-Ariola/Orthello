#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "Player.hpp"
#include <iostream>
#include <memory>

class GameManager {
  public:
    GameManager();
    ~GameManager();
  
    bool StartGame();

    //Properties
    bool GetIsGameComplete();

  private:
  bool InitializePlayers();
  bool isGameComplete = false;
  std::shared_ptr<Player> player1_ptr {};
  std::shared_ptr<Player> player2_ptr {};
  
};

#endif