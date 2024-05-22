#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "Player.hpp"
#include <iostream>
#include <cstring>
#include <cctype>
#include <memory>

enum class GameState {InitializeGame, AnalyzeBoard, PrintBoard, PlayerTurn, UpdateBoard};

class GameManager {
  public:
    GameManager();
    ~GameManager();
    
    //Field
    static const int BOARD_LENGTH{8};
  
    //Methods
    bool StartGame();
    bool Update();
    bool PrintGameboard();

    //Properties
    bool GetIsGameComplete();
    
  private:
    //Fields
    bool _isGameComplete = false;
    bool _isPlayer1Turn = true;
    std::shared_ptr<Player> _player1_ptr {};
    std::shared_ptr<Player> _player2_ptr {};
    std::shared_ptr<Player> _current_player_ptr {};
    char _othello_gameboard[BOARD_LENGTH][BOARD_LENGTH];
    
    GameState _current_state{GameState::InitializeGame};

    //Methods
    bool InitializePlayers();
    bool InsertPlayerPieceByCoordinates(const std::string &placement_coordinates_string, const std::shared_ptr<Player> &current_player_ptr);
    bool InsertPieceByIndex(int row, int column, char piece);
    std::string AskPlayerForPlacementCoordinates(const std::shared_ptr<Player> &current_player_ptr);
};


#endif