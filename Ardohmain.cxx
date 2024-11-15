#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

class RandomPlayer {
public:
    char name;
    RandomPlayer(char playerName) : name(playerName) {}  // Constructor to set player name
    void SelectLineLocation(int actualRows, int actualColumns, char** board, int emptyLocations[][2], int emptyCount, char playername);
};

class StrategicPlayer {
public:
    char name;
    StrategicPlayer(char playerName) : name(playerName) {}  // Constructor to set player name
    void SelectLineLocation(int actualRows, int actualColumns, char** board, int emptyLocations[][2], int emptyCount, char playername);
};

class Board {
public:
    char** board;  // Pointer to the 2D board
    int actualRows, actualColumns;

    // Constructor to initialize the board
    Board(int rows, int columns) {
        actualRows = rows;
        actualColumns = columns;
        board = initialize_board(rows, columns);  // Initialize the board
    }

    // Destructor to clean up the dynamically allocated memory
    ~Board() {
        for (int i = 0; i < actualRows; ++i) {
            delete[] board[i];  // Free each row
        }
        delete[] board;  // Free the board array
    }

    char** initialize_board(int actualRows, int actualColumns);
    void print_board(int actualRows, int actualColumns, char** board);
    int GetAllEmptyLineLocations(int actualRows, int actualColumns, char** board, int emptyLocations[][2]);
    void PlaceCharacterInRandomEmptySpot(int actualRows, int actualColumns, char** board, int emptyLocations[][2], int emptyCount, char character);
};


int main (){

    // initialize variables 
    std::string playerstatus;
    char player1char;
    char player2char;
    int rows;
    int columns;
    bool gameOn = true;
    int emptyLocations[rows * columns][2];

    // Open file for the game inputs
    std::ifstream gamefile("input1.txt");

    // Check if the file was successfully opened
    if (!gamefile) {
        std::cerr << "Error: The file cannot be opened." << std::endl;
        return 1;
    }

    // Get the board size from the file
    gamefile >> rows >> columns;

    // Validate the board dimensions
    if (rows <= 0 || columns <= 0) {
        std::cerr << "Error: Invalid board dimensions." << std::endl;
        return 1;
    }

    // Adjusting the size of the board for alternating dots and spaces
    int actualRows = 2 * rows;
    int actualColumns = ((2 * columns) - 1);

    // Creating the game board dynamically
    Board board(actualRows, actualColumns);  // Constructor initializes the board
    char** Fboard = board.board;

    // assign players
    
    

    gamefile>>player1char>>playerstatus >> player2char;

    bool starter = false;
    // Declare player objects outside the if block so they persist
    RandomPlayer* RPlayer = nullptr;
    StrategicPlayer* SPlayer = nullptr;

    if (playerstatus == "Random") {
        starter = true;
        RPlayer = new RandomPlayer(player1char);  // Initialize RandomPlayer
        SPlayer = new StrategicPlayer(player2char);  // Initialize StrategicPlayer
    } else if (playerstatus == "Strategic") {
        starter = true;
        RPlayer = new RandomPlayer(player2char);  // Initialize RandomPlayer
        SPlayer = new StrategicPlayer(player1char);  // Initialize StrategicPlayer
    } else {
        std::cout << "Can't determine Player. Check input." << std::endl;
    }
    
    //get empty board location 
    int emptyCount = board.GetAllEmptyLineLocations( actualRows,  actualColumns, Fboard, emptyLocations);
    //main game loop 
    if (starter){
        while (gameOn) {
            RPlayer->SelectLineLocation(actualRows, actualColumns, Fboard, emptyLocations, emptyCount, RPlayer->name);
            break;
        };
    }
        


    return 0;
}

char **Board::initialize_board(int actualRows, int actualColumns) {
    char** board = new char*[actualRows];  // Allocate memory for rows
    for (int i = 0; i < actualRows; ++i) {
        board[i] = new char[actualColumns];  // Allocate memory for columns in each row
        if (i % 2 == 0) {  // Fill with dots and spaces
            for (int j = 0; j < actualColumns; ++j) {
                board[i][j] = (j % 2 == 0) ? '.' : ' ';
            }
        } else {  // Fill with spaces
            for (int j = 0; j < actualColumns; ++j) {
                board[i][j] = ' ';
            }
        }
    }
    return board;  // Return the allocated board
}

void Board::print_board(int actualRows, int actualColumns, char **board){
    // Print the final board state
        std::cout << "  ";  // Leading space for row numbers
        for (int col = 0; col < actualColumns; ++col) {
            if (col % 10 == 0) {
                std::cout << col / 10;  // Print tens place for column numbers
            } else {
                std::cout << " ";  // Space for non-tens place
            }
        }
        std::cout << std::flush;
        std::cout << std::endl;

        std::cout << "  ";  // Space for row numbers
        for (int col = 0; col < actualColumns; ++col) {
            std::cout << (col % 10);  // Print ones place for column numbers
        }
        std::cout << std::flush;
        std::cout << std::endl;

        // Print the board
        for (int i = 0; i < actualRows-1; ++i) {
            std::cout << (i % 10) << " ";  // Print row numbers
            for (int j = 0; j < actualColumns; ++j) {
                std::cout << board[i][j];
            }
            std::cout << std::endl;
        }
}

int Board::GetAllEmptyLineLocations(int actualRows, int actualColumns, char** board, int emptyLocations[][2]) {
    int count = 0;

    // Traverse the board to find empty spots (assuming empty is represented by ' ')
    for (int i = 0; i < actualRows; ++i) {
        for (int j = 0; j < actualColumns; ++j) {
            if (board[i][j] == ' ') {  // Empty spot is represented by space ' '
                emptyLocations[count][0] = i;  // Store the row index
                emptyLocations[count][1] = j;  // Store the column index
                ++count;  // Increment the count of empty spots
            }
        }
    }

    return count;  // Return the number of empty spots
}

void RandomPlayer::SelectLineLocation(int actualRows, int actualColumns, char** board, int emptyLocations[][2], int emptyCount, char playername) {

    if (emptyCount == 0) {
        std::cout << "No empty spots available!" << std::endl;
        return;
    }

    // Select a random empty spot
    int randomIndex = rand() % emptyCount;  // Get a random index using custom_rand
    int row = emptyLocations[randomIndex][0];
    int col = emptyLocations[randomIndex][1];

    // Place the specified character in the selected spot
    board[row][col] = tolower(playername);

    // Print a move
    std::cout <<playername << " " <<row << col << std::endl;
}
