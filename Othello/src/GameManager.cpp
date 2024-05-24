#include "GameManager.hpp"

GameManager::GameManager() {
  std::memset(_othello_gameboard, EMPLY_PLACE_PIECE_CHAR, sizeof(_othello_gameboard));
}

GameManager::~GameManager() {
  _player1_ptr = nullptr;
  _player2_ptr = nullptr;
  _current_player_ptr = nullptr;
}

bool GameManager::StartGame() {
  InitializePlayers();

  //No player info
  if(!_player1_ptr || !_player2_ptr) return false;

  //_player_1 starting pieces
  InsertPlayerPieceByCoordinates("E4", _player1_ptr, true);
  InsertPlayerPieceByCoordinates("D5", _player1_ptr, true);

  //_player_2 starting pieces
  InsertPlayerPieceByCoordinates("D4", _player2_ptr, true);
  InsertPlayerPieceByCoordinates("E5", _player2_ptr, true);

  _current_state = GameState::AnalyzeBoard;
  _current_player_ptr = _player1_ptr;
  return true;
}

bool GameManager::Update() {
  std::shared_ptr current_player_ptr = (_isPlayer1Turn) ? _player1_ptr : _player2_ptr;
  std::shared_ptr oppposing_player_ptr = (_isPlayer1Turn) ? _player2_ptr : _player1_ptr;

  switch (_current_state)
  {
    case GameState::AnalyzeBoard: {
      std::vector<coordinates> placed_coordinates = GetCurrentPlayerPlacedCoordinates(current_player_ptr);
      std::vector<coordinates> possible_coordinates = GetPossiblePlacementCoordinates(current_player_ptr, placed_coordinates);
      
      for (auto coord : possible_coordinates) {
        InsertPieceByIndex(coord.x, coord.y, POSSIBLE_PLACE_PIECE_CHAR);
      }
      if (_number_of_turns_counter > MAX_NUM_OF_TURNS) {
        _isGameComplete = true;
        return true;
      }
      ++_number_of_turns_counter;

      if (possible_coordinates.size() == 0) {
        _times_player_skipped++;
        std::cout << "PLAYER " << current_player_ptr->GetName() << " TURN SKIPPED!" << std::endl;
        if (_times_player_skipped < 2) {
          _current_state = GameState::ResetForNextTurn;
          break;
        } 
          _isGameComplete = true;
          return true;
      }

      if (_times_player_skipped >= 2) {
        _isGameComplete = true;
        break;
      }

      _current_state = GameState::PrintBoard;
      break;
    }

    case GameState::PrintBoard: {
      PrintGameboard();
      _current_state = GameState::PlayerTurn;
      break;    
    }

    case GameState::PlayerTurn: {
      std::string input_coordinates = AskPlayerForPlacementCoordinates(current_player_ptr);
      
      if (input_coordinates == "QUIT") {
        _isGameComplete = true;
        return true;
      }
      
      if (!InsertPlayerPieceByCoordinates(input_coordinates, current_player_ptr)) {
        std::cerr << "INVALID PLACEMENT, TRY AGAIN" << std::endl;
        return true;
      }

      _current_player_placed_string = input_coordinates;
      std::cout << "Piece placed at: "<< _current_player_placed_string << std::endl;
      _current_state = GameState::UpdateBoard;
      break;
    }
    
    case GameState::UpdateBoard: {
      //Player piece has been placed in Player Turn
      //No resolve the possible places
      std::vector<coordinates> pieces_to_flip_coordinates{};
      coordinates placed_piece_coordinates = BoardCoordinateUtils::StringCoordinatesToArrayIndeces(_current_player_placed_string);

      std::cout << placed_piece_coordinates << std::endl;
      std::vector<coordinates> left_pieces_to_flip_coordinates = 
        GetPiecesToFlipCoordinates(placed_piece_coordinates, current_player_ptr->GetPiece(), oppposing_player_ptr->GetPiece(), 0, -1);
      std::vector<coordinates> right_pieces_to_flip_coordinates = 
        GetPiecesToFlipCoordinates(placed_piece_coordinates, current_player_ptr->GetPiece(), oppposing_player_ptr->GetPiece(), 0, 1);
      std::vector<coordinates> up_pieces_to_flip_coordinates = 
        GetPiecesToFlipCoordinates(placed_piece_coordinates, current_player_ptr->GetPiece(), oppposing_player_ptr->GetPiece(), -1);
      std::vector<coordinates> down_pieces_to_flip_coordinates = 
        GetPiecesToFlipCoordinates(placed_piece_coordinates, current_player_ptr->GetPiece(), oppposing_player_ptr->GetPiece(), 1);
      std::vector<coordinates> up_left_pieces_to_flip_coordinates = 
        GetPiecesToFlipCoordinates(placed_piece_coordinates, current_player_ptr->GetPiece(), oppposing_player_ptr->GetPiece(), -1, -1);
      std::vector<coordinates> up_right_pieces_to_flip_coordinates = 
        GetPiecesToFlipCoordinates(placed_piece_coordinates, current_player_ptr->GetPiece(), oppposing_player_ptr->GetPiece(), -1, 1);
      std::vector<coordinates> down_left_pieces_to_flip_coordinates = 
        GetPiecesToFlipCoordinates(placed_piece_coordinates, current_player_ptr->GetPiece(), oppposing_player_ptr->GetPiece(), 1, -1);
      std::vector<coordinates> down_right_pieces_to_flip_coordinates = 
        GetPiecesToFlipCoordinates(placed_piece_coordinates, current_player_ptr->GetPiece(), oppposing_player_ptr->GetPiece(), 1, 1);

      pieces_to_flip_coordinates.insert(pieces_to_flip_coordinates.end(), left_pieces_to_flip_coordinates.begin(), left_pieces_to_flip_coordinates.end());
      pieces_to_flip_coordinates.insert(pieces_to_flip_coordinates.end(), right_pieces_to_flip_coordinates.begin(), right_pieces_to_flip_coordinates.end());
      pieces_to_flip_coordinates.insert(pieces_to_flip_coordinates.end(), up_pieces_to_flip_coordinates.begin(), up_pieces_to_flip_coordinates.end());
      pieces_to_flip_coordinates.insert(pieces_to_flip_coordinates.end(), down_pieces_to_flip_coordinates.begin(), down_pieces_to_flip_coordinates.end());
      pieces_to_flip_coordinates.insert(pieces_to_flip_coordinates.end(), up_left_pieces_to_flip_coordinates.begin(), up_left_pieces_to_flip_coordinates.end());
      pieces_to_flip_coordinates.insert(pieces_to_flip_coordinates.end(), up_right_pieces_to_flip_coordinates.begin(), up_right_pieces_to_flip_coordinates.end());
      pieces_to_flip_coordinates.insert(pieces_to_flip_coordinates.end(), down_left_pieces_to_flip_coordinates.begin(), down_left_pieces_to_flip_coordinates.end());
      pieces_to_flip_coordinates.insert(pieces_to_flip_coordinates.end(), down_right_pieces_to_flip_coordinates.begin(), down_right_pieces_to_flip_coordinates.end());

      for (auto coords : pieces_to_flip_coordinates) {
        InsertPieceByIndex(coords.x, coords.y, current_player_ptr->GetPiece());
      }
      _current_state = GameState::ResetForNextTurn;
      break;
    }

    case GameState::ResetForNextTurn: {
      //Remove possible places pieces from game board
      for (int row = 0; row < BOARD_LENGTH; row++) {
        for (int col = 0; col < BOARD_LENGTH; col++) {
          if (_othello_gameboard[row][col] == POSSIBLE_PLACE_PIECE_CHAR) {
            InsertPieceByIndex(row, col, EMPLY_PLACE_PIECE_CHAR);
          }
        }
      }

      _isPlayer1Turn = !_isPlayer1Turn;
      _current_player_placed_string = "";
      _current_state = GameState::AnalyzeBoard;
      break;
    }

  }
  return true;
}

bool GameManager::EndGame() {
  PrintGameboard();
  std::cout << "Tally points" << std::endl;
  char player_1_piece = _player1_ptr->GetPiece();
  char player_2_piece = _player2_ptr->GetPiece();
  unsigned int player1_points{0};
  unsigned int player2_points{0};  

  for(int row = 0; row < BOARD_LENGTH; row++) {
    for (int col = 0; col < BOARD_LENGTH; col++) {
      char current_piece = _othello_gameboard[row][col];
      if (current_piece == player_1_piece) {
        ++player1_points;
        continue;
      }
      if (current_piece == player_2_piece) {
        ++player2_points;
        continue;
      }
    }
  }

  std::cout << "Player 1 points: " << player1_points << std::endl;
  std::cout << "Player 2 points: " << player2_points << std::endl;

  if (player1_points > player2_points) {
    std::cout << _player1_ptr->GetName() << " wins!" << std::endl;
    return true;
  }
  if (player1_points < player2_points) {
    std::cout << _player2_ptr->GetName() << " wins!" << std::endl;
    return true;
  }
  std::cout << "It is a draw, good job " << _player1_ptr->GetName() << " & " << _player2_ptr->GetName() << std::endl;
  return true;
}

bool GameManager::PrintGameboard() {
  const int row_length = BOARD_LENGTH;
  const int column_length = BOARD_LENGTH;
  const char alpha_indicators[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  const signed int HORIZONTAL_SPACE = 4;
  const char LINE_CHAR{'='};
  
  std::cout << "\t\t ";
  for (auto c = 0; c < column_length; c++) {
    std::cout << "   " << alpha_indicators[c];
  }
  std::cout << std::endl;

  std::cout << "\t\t=";
  for (auto c = 0; c < column_length; c++) {
    std::string line{std::string(HORIZONTAL_SPACE, LINE_CHAR)};
    std::cout << line;
  }
  std::cout << std::endl;

  for (auto r = 0; r < row_length; r++) {
    std::cout << "\t\t" << r + 1;
    for (auto c = 0; c < column_length; c++) {
      std::cout << "   " << _othello_gameboard[r][c];
    }
    std::cout << std::endl;
  }
  return true;
}

bool GameManager::GetIsGameComplete() {
  return _isGameComplete;
}


bool GameManager::InitializePlayers(bool is_debugging) {
  if (is_debugging) {
  std::shared_ptr<Player> new_p1_ptr {new Player("Dom", 'D')};
  std::shared_ptr<Player> new_p2_ptr {new Player("Ter", 'T')};
  _player1_ptr = new_p1_ptr;
  _player2_ptr = new_p2_ptr;
    return true;
  }

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
      _player1_ptr = new_player_ptr;
    } else {
      _player2_ptr = new_player_ptr;
    }
    
    playerCount++;
    new_player_ptr = nullptr;
  }

  return true;
}

std::string GameManager::AskPlayerForPlacementCoordinates(const std::shared_ptr<Player> &current_player_ptr) {
  std::string input_coordinates{};
  bool isValidInput{false};

  while (!isValidInput) {
  std::cout << "Player " << current_player_ptr->GetName() << ", enter the coordinates (EX. \"d3\") of the grid where you want to play: ";
  std::cin >> input_coordinates;
  
  if (input_coordinates == "QUIT") return "QUIT";

  isValidInput = BoardCoordinateUtils::IsValidCoordinates(input_coordinates);
    if (!isValidInput) {
      std::cout << "Invalid input. Please try again " << current_player_ptr->GetName() << std::endl;
    }
  }
  input_coordinates[0] = std::toupper(input_coordinates[0]);

  return input_coordinates;
}

bool GameManager::InsertPlayerPieceByCoordinates(const std::string &placement_coordinates_string,
  const std::shared_ptr<Player> &current_player_ptr,
  const bool ignore_placement_rules) {
  coordinates coordinates = BoardCoordinateUtils::StringCoordinatesToArrayIndeces(placement_coordinates_string);

  if (coordinates.x >= BOARD_LENGTH || coordinates.y >= BOARD_LENGTH) return false;
  if (_othello_gameboard[coordinates.x][coordinates.y] != '0' && !ignore_placement_rules) return false;

  // _othello_gameboard[coordinates.x][coordinates.y] = current_player_ptr->GetPiece();
  InsertPieceByIndex(coordinates.x, coordinates.y, current_player_ptr->GetPiece());

  return true;
}

bool GameManager::InsertPieceByIndex(int row, int column, char piece) {
  _othello_gameboard[row][column] = piece;
  return true;
}

std::vector<coordinates> GameManager::GetCurrentPlayerPlacedCoordinates(const std::shared_ptr<Player> &current_player_ptr) {
  std::vector<coordinates> player_placed_coordinates;
  char player_piece = current_player_ptr->GetPiece();

  for (auto r = 0; r < BOARD_LENGTH; r++) {
    for (auto c = 0; c < BOARD_LENGTH; c++) {
      if (_othello_gameboard[r][c] == player_piece){
        coordinates placed_coords;
        placed_coords.x = r;
        placed_coords.y = c;
        player_placed_coordinates.push_back(placed_coords);
      }
    }
  }

  return player_placed_coordinates;
}

std::vector<coordinates> GameManager::GetPossiblePlacementCoordinates(const std::shared_ptr<Player> &current_player_ptr, const std::vector<coordinates> &placed_coordinates) {
  std::vector<coordinates> possible_to_place_coordinates;
  char player_piece = current_player_ptr->GetPiece();
  char opponent_piece = (_isPlayer1Turn) ? _player2_ptr->GetPiece() : _player1_ptr->GetPiece();

  for (auto coordinates : placed_coordinates) {
    //Checking left
    AddCoordinatesByIncrementDirection(possible_to_place_coordinates, coordinates, player_piece, opponent_piece, 0, -1);
    //Checking right
    AddCoordinatesByIncrementDirection(possible_to_place_coordinates, coordinates, player_piece, opponent_piece, 0, 1);    
    //Checking up
    AddCoordinatesByIncrementDirection(possible_to_place_coordinates, coordinates, player_piece, opponent_piece, -1);    
    //Checking down
    AddCoordinatesByIncrementDirection(possible_to_place_coordinates, coordinates, player_piece, opponent_piece, 1);    
    //Checking up-left
    AddCoordinatesByIncrementDirection(possible_to_place_coordinates, coordinates, player_piece, opponent_piece, -1, -1);    
    //Checking up-right
    AddCoordinatesByIncrementDirection(possible_to_place_coordinates, coordinates, player_piece, opponent_piece, -1, 1);    
    //Checking down-left
    AddCoordinatesByIncrementDirection(possible_to_place_coordinates, coordinates, player_piece, opponent_piece, 1, -1);    
    //Checking down-right
    AddCoordinatesByIncrementDirection(possible_to_place_coordinates, coordinates, player_piece, opponent_piece, 1, 1);    

  }
  return possible_to_place_coordinates;
}

bool GameManager::AddCoordinatesByIncrementDirection(
  std::vector<coordinates> &possible_to_place_coordinates, 
  const coordinates &startingCoordinates, 
  const char &current_player_piece,
  const char &opposing_player_piece,
  const int increment_row_val, 
  const int increment_col_val
) {
  if (std::abs(increment_col_val) > 1 || std::abs(increment_row_val) > 1) return false;

  bool has_encountered_opposing_piece{false};

  for (int row = startingCoordinates.x + increment_row_val, col = startingCoordinates.y + increment_col_val;
    (row >= 0 && row < BOARD_LENGTH) && (col >= 0 && col < BOARD_LENGTH);
    row += increment_row_val, col += increment_col_val) {

    char current_piece = _othello_gameboard[row][col];

    if (current_piece == current_player_piece) break;
    if (current_piece == opposing_player_piece) {
      has_encountered_opposing_piece = true;
      continue;
    }
    if (has_encountered_opposing_piece && current_piece != opposing_player_piece) {
      coordinates temp_coordinates;
      temp_coordinates.x = row;
      temp_coordinates.y = col;
      possible_to_place_coordinates.push_back(temp_coordinates);
      break;
    }
    if (!has_encountered_opposing_piece && current_piece != opposing_player_piece) break;

  }

  return true;
}

std::vector<coordinates> GameManager::GetPiecesToFlipCoordinates (const coordinates &placed_coordinates,
  const char &current_player_piece,
  const char &opposing_player_piece,
  const int increment_row_val, 
  const int increment_col_val
      ) {
        std::vector<coordinates> result_coordinates{};
        if (std::abs(increment_col_val) > 1 || std::abs(increment_row_val) > 1) return result_coordinates;
        
        for (int row = placed_coordinates.x + increment_row_val, col = placed_coordinates.y + increment_col_val; 
          (row >= 0 && row < BOARD_LENGTH) && (col >= 0 && col < BOARD_LENGTH);
          row += increment_row_val, col += increment_col_val) {
          char current_piece = _othello_gameboard[row][col];
          

          if (current_piece == current_player_piece) return result_coordinates;
          if (current_piece == opposing_player_piece) {
            if (row + increment_row_val < 0 || row + increment_row_val == BOARD_LENGTH) return std::vector<coordinates> {};
            if (col + increment_col_val < 0 || col + increment_col_val == BOARD_LENGTH) return std::vector<coordinates> {};
            coordinates pieces_to_flip_coordinates;
            pieces_to_flip_coordinates.x = row; 
            pieces_to_flip_coordinates.y = col;
            result_coordinates.push_back(pieces_to_flip_coordinates);
            continue;
            } 
          return std::vector<coordinates> {};
        }

        return result_coordinates;
      }

bool GameManager::PrintVectorOfCoordinates (const std::vector<coordinates> &vec) {
  for (auto coord : vec) {
    std::cout << coord << " ";
  }
  std::cout << std::endl;
  return true;
}