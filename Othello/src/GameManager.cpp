#include "GameManager.hpp"
#include "BoardCoordinateUtils.cpp"

GameManager::GameManager() {
  std::memset(_othello_gameboard, '.', sizeof(_othello_gameboard));
  std::cout << "Game Manager initialized." << std::endl;
}

GameManager::~GameManager() {
  std::cout << "Game Manager deconstructed" << std::endl;
  _player1_ptr = nullptr;
  _player2_ptr = nullptr;
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

  PrintGameboard();
  _current_state = GameState::AnalyzeBoard;
  _current_player_ptr = _player1_ptr;
  return true;
}

bool GameManager::Update() {
  switch (_current_state)
  {
    case GameState::AnalyzeBoard: 

    break;

    case GameState::PrintBoard:

    break;    

    case GameState::PlayerTurn:

    break;

    case GameState::UpdateBoard:
    
    break;
  }

  std::string input_coordintates = AskPlayerForPlacementCoordinates(current_player_ptr);
  InsertPlayerPieceByCoordinates(input_coordintates,current_player_ptr);
  PrintGameboard();
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
  std::shared_ptr<Player> new_p2_ptr {new Player("Ter", 'F')};

  _player1_ptr = new_p1_ptr;
  _player2_ptr = new_p2_ptr;

  return true;
}

//TODO: Print the Orthello Game board with grid indicators
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
  
  isValidInput = BoardCoordinateUtils::IsValidCoordinates(input_coordinates);
    if (!isValidInput) {
      std::cout << "Invalid input. Please try again " << current_player_ptr->GetName() << std::endl;
    }
  }
  input_coordinates[0] = std::toupper(input_coordinates[0]);
  std::cout << "User input: " << input_coordinates << std::endl;

  return input_coordinates;
}