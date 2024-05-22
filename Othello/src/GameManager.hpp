#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "Player.hpp"
#include "BoardCoordinateUtils.cpp"
#include <iostream>
#include <cstring>
#include <cctype>
#include <map>
#include <memory>
#include <vector>

enum class GameState {AnalyzeBoard, PrintBoard, PlayerTurn, UpdateBoard};
static const int BOARD_LENGTH{8};

class GameManager {
  public:
    GameManager();
    ~GameManager();
    
    //Field
  
    //Methods
    bool StartGame();
    bool Update();
    bool PrintGameboard();
    std::vector<BoardCoordinateUtils::coordinates> GetCurrentPlayerPlacedCoordinates(const std::shared_ptr<Player> &current_player_ptr);
    std::vector<BoardCoordinateUtils::coordinates> GetPossiblePlacementCoordinates(const std::shared_ptr<Player> &current_player_ptr, const std::vector<BoardCoordinateUtils::coordinates> &placed_coordinates);

    //Properties
    bool GetIsGameComplete();
    
  private:
    //Fields
    bool _isGameComplete {false};
    bool _isPlayer1Turn {true};
    std::shared_ptr<Player> _player1_ptr {nullptr};
    std::shared_ptr<Player> _player2_ptr {nullptr};
    std::shared_ptr<Player> _current_player_ptr {nullptr};
    char _othello_gameboard[BOARD_LENGTH][BOARD_LENGTH];
    int _times_player_skipped{0};
    int _number_of_turns_counter{1};
    int MAX_NUM_OF_TURNS{64};
    GameState _current_state{GameState::AnalyzeBoard};

    //Methods
    bool InitializePlayers();
    bool InsertPlayerPieceByCoordinates(const std::string &placement_coordinates_string, const std::shared_ptr<Player> &current_player_ptr, const bool is_setting_up = false);
    bool InsertPieceByIndex(int row, int column, char piece);
    std::string AskPlayerForPlacementCoordinates(const std::shared_ptr<Player> &current_player_ptr);
    bool PrintVectorOfCoordinates (const std::vector<BoardCoordinateUtils::coordinates> &vec);
    bool AddCoordinatesByIncrementDirection(
      std::vector<BoardCoordinateUtils::coordinates> &possible_to_place_coordinates, 
      const BoardCoordinateUtils::coordinates &startingCoordinates, 
      const char &current_player_piece,
      const char &opposing_player_piece,
      int increment_col_val = 0, 
      int increment_row_val = 0
    );
};


#endif