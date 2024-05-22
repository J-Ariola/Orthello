#include "GameManager.hpp"

GameManager::GameManager() {
  std::memset(_othello_gameboard, '.', sizeof(_othello_gameboard));
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
  InsertPlayerPieceByCoordinates("E4", _player1_ptr);
  InsertPlayerPieceByCoordinates("D5", _player1_ptr);

  //_player_2 starting pieces
  InsertPlayerPieceByCoordinates("D4", _player2_ptr);
  InsertPlayerPieceByCoordinates("E5", _player2_ptr);

  _current_state = GameState::AnalyzeBoard;
  _current_player_ptr = _player1_ptr;
  return true;
}

bool GameManager::Update() {
  std::shared_ptr current_player_ptr = (_isPlayer1Turn) ? _player1_ptr : _player2_ptr;
  switch (_current_state)
  {
    case GameState::AnalyzeBoard: {
      std::cout << "Analyze" << std::endl;
      std::vector<BoardCoordinateUtils::coordinates> placed_coordinates = GetCurrentPlayerPlacedCoordinates(current_player_ptr);
      PrintVectorOfCoordinates(placed_coordinates);
        if (_times_player_skipped >= 2) {
          _isGameComplete = true;
          break;
        }
        if (_number_of_turns_counter > MAX_NUM_OF_TURNS) {
          _isGameComplete = true;
          break;
        }
        ++_number_of_turns_counter;
      _current_state = GameState::PrintBoard;
      break;
    }

    case GameState::PrintBoard: {
      std::cout << "Print" << std::endl;
      PrintGameboard();
      _current_state = GameState::PlayerTurn;
      break;    
    }

    case GameState::PlayerTurn: {
      std::cout << "Player Turn" << std::endl;

      std::string input_coordinates = AskPlayerForPlacementCoordinates(current_player_ptr);

      if (input_coordinates == "QUIT") {
        _isGameComplete = true;
        return true;
      }

      InsertPlayerPieceByCoordinates(input_coordinates, current_player_ptr);
      current_player_ptr = _player2_ptr;
      _current_state = GameState::AnalyzeBoard;
      break;
    }
  }
  return true;
}

bool GameManager::InitializePlayers() {
  unsigned int playerCount {1};

  // while (playerCount <= 2) {
  //   std::string name{""};
  //   char piece_char{};

  //   std::cout << "Please enter player " << playerCount << "\'s name: ";
  //   std::cin >> name;
  //   std::cout << std::endl;

  //   std::cout << "Welcome " << name << ", please enter a single character to represent your piece: ";
  //   std::cin >> piece_char;

  //   std::shared_ptr<Player> new_player_ptr {new Player(name, piece_char)};
  //   new_player_ptr->DisplayPlayerInfo();

  //   if (playerCount == 1) {
  //     _player1_ptr = new_player_ptr;
  //   } else {
  //     _player2_ptr = new_player_ptr;
  //   }
    
  //   playerCount++;
  //   new_player_ptr = nullptr;
  // }

  std::shared_ptr<Player> new_p1_ptr {new Player("Dom", 'D')};
  std::shared_ptr<Player> new_p2_ptr {new Player("Ter", 'T')};

  _player1_ptr = new_p1_ptr;
  _player2_ptr = new_p2_ptr;

  return true;
}

bool GameManager::PrintGameboard() {
  const int row_length = BOARD_LENGTH;
  const int column_length = BOARD_LENGTH;
  const char alpha_indicators[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  const signed int HORIZONTAL_SPACE = 4;
  const char LINE_CHAR{'='};
  
  std::cout << " ";
  for (auto c = 0; c < column_length; c++) {
    std::cout << "   " << alpha_indicators[c];
  }
  std::cout << std::endl;

  std::cout << "=";
  for (auto c = 0; c < column_length; c++) {
    std::string line{std::string(HORIZONTAL_SPACE, LINE_CHAR)};
    std::cout << line;
  }
  std::cout << std::endl;

  // for (auto c = 0; c < column_length; c++) {
  //   std::cout << "1234567890";
  // }
  // std::cout << std::endl;

  for (auto r = 0; r < row_length; r++) {
    std::cout << r + 1;
    for (auto c = 0; c < column_length; c++) {
      std::cout << "   " << _othello_gameboard[r][c];
    }
    std::cout << std::endl;
  }
  return true;
}

std::vector<BoardCoordinateUtils::coordinates> GameManager::GetCurrentPlayerPlacedCoordinates(const std::shared_ptr<Player> &current_player_ptr) {
  std::vector<BoardCoordinateUtils::coordinates> player_placed_coordinates;
  char player_piece = current_player_ptr->GetPiece();

  for (auto r = 0; r < BOARD_LENGTH; r++) {
    for (auto c = 0; c < BOARD_LENGTH; c++) {
      if (_othello_gameboard[r][c] == player_piece){
        BoardCoordinateUtils::coordinates placed_coords;
        placed_coords.x = r;
        placed_coords.y = c;
        player_placed_coordinates.push_back(placed_coords);
      }
    }
  }

  return player_placed_coordinates;
}

std::vector<BoardCoordinateUtils::coordinates> GameManager::GetPossiblePlacementCoordinates(const std::shared_ptr<Player> &current_player_ptr, const std::vector<BoardCoordinateUtils::coordinates> &placed_coordinates) {
  std::vector<BoardCoordinateUtils::coordinates> possible_to_place_coordinates;
  char player_piece = current_player_ptr->GetPiece();
  char opponent_piece = (_isPlayer1Turn) ? _player2_ptr->GetPiece() : _player1_ptr->GetPiece();

  for (auto coordinates : placed_coordinates) {
    //Checking left
    for (auto row = coordinates.x - 1; row >= 0; row--) {
      bool has_encountered_opposing_piece{false};
      bool current_piece = _othello_gameboard[row][coordinates.y];
      if (current_piece == player_piece) break;
      if (current_piece == opponent_piece) {
        has_encountered_opposing_piece = true;
        continue;
      }
      if (has_encountered_opposing_piece && current_piece != opponent_piece) {
        BoardCoordinateUtils::coordinates temp_coordinates;
        temp_coordinates.x = row;
        temp_coordinates.y = coordinates.y;
        possible_to_place_coordinates.push_back(temp_coordinates);
        break;
      }
    }
    //Checking right
    for (auto row = coordinates.x; row < BOARD_LENGTH; row++) {
      
    }
    //Checking up
    //Checking down
    //Checking up-left
    //Checking up-right
    //Checking down-left
    //Checking down-right

    coordinates<<(std::cout) << std::endl;
  }

  return possible_to_place_coordinates;
}

bool GameManager::InsertPlayerPieceByCoordinates(const std::string &placement_coordinates_string, const std::shared_ptr<Player> &current_player_ptr) {
  BoardCoordinateUtils::coordinates coordinates = BoardCoordinateUtils::StringCoordinatesToArrayIndeces(placement_coordinates_string);
  std::cout << "Inserting " << current_player_ptr->GetName() << ": " << current_player_ptr->GetPiece() 
  << " into [" << coordinates.x << ", " << coordinates.y << "]" << std::endl;

  if (coordinates.x >= BOARD_LENGTH || coordinates.y >= BOARD_LENGTH) return false;

  _othello_gameboard[coordinates.x][coordinates.y] = current_player_ptr->GetPiece();

  return true;
}

bool GameManager::GetIsGameComplete() {
  return _isGameComplete;
}

std::string GameManager::AskPlayerForPlacementCoordinates(const std::shared_ptr<Player> &current_player_ptr) {
  std::string input_coordinates{};
  bool isValidInput{false};

  while (!isValidInput) {
  std::cout << "Player " << current_player_ptr->GetName() << ", enter the coordinates (EX. \"D3\") of the grid where you want to play: ";
  std::cin >> input_coordinates;
  
  if (input_coordinates == "QUIT") return "QUIT";

  isValidInput = BoardCoordinateUtils::IsValidCoordinates(input_coordinates);
    if (!isValidInput) {
      std::cout << "Invalid input. Please try again " << current_player_ptr->GetName() << std::endl;
    }
  }
  input_coordinates[0] = std::toupper(input_coordinates[0]);
  std::cout << "User input: " << input_coordinates << std::endl;

  return input_coordinates;
}

bool GameManager::PrintVectorOfCoordinates (const std::vector<BoardCoordinateUtils::coordinates> &vec) {
  for (auto coord : vec) {
    coord.operator<<(std::cout) << " ";
  }
  std::cout << std::endl;
  return true;
}