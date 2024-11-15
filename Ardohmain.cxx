#include <iostream>
#include <fstream>

class RandomPlayer {
    public:
        std::string name;
        void SelectLineLocation();    
};

class StrategicPlayer{ 
    public:
        std::string name;
        void SelectLineLocation();
};




int main (){

    // initialize variables 
    std::string playerstatus;
    char player1char;
    char player2char;
    int rows;
    int columns;


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
    char** board = new char*[actualRows];
    for (int i = 0; i < actualRows; ++i) {
        board[i] = new char[actualColumns];

        // Fill board based on the specified format
        if (i % 2 == 0) {  // Rows with dots
            for (int j = 0; j < actualColumns; ++j) {
                board[i][j] = (j % 2 == 0) ? '.' : ' ';  // Dot in even columns, space in odd
            }
        } else {  // Rows with spaces
            for (int j = 0; j < actualColumns; ++j) {
                board[i][j] = ' ';  // All spaces
            }
        }
    }

    // assingn players 
    RandomPlayer RandomPlayer;
    StrategicPlayer StrategicPlayer;

    gamefile>>player1char>>playerstatus >> player2char;

    if (playerstatus=="Random"){
        RandomPlayer.name = player1char;
        StrategicPlayer.name = player2char;
    }else if (playerstatus=="Strategic"){
        RandomPlayer.name = player2char;
        StrategicPlayer.name = player1char;
    }
    
    // tester 
    std::cout<< "strategic player :" << StrategicPlayer.name<< "and "<< RandomPlayer.name<<std::endl;

    //main game loop 
    while (true) {
        std::cout << "enter is player "<<player1char<<"move";
        break;
    };


return 0;
}

void initialize_board (int actualRows,int actualColumns ){
char** board = new char*[actualRows];
    for (int i = 0; i < actualRows; ++i) {
        board[i] = new char[actualColumns];

        // Fill board based on the specified format
        if (i % 2 == 0) {  // Rows with dots
            for (int j = 0; j < actualColumns; ++j) {
                board[i][j] = (j % 2 == 0) ? '.' : ' ';  // Dot in even columns, space in odd
            }
        } else {  // Rows with spaces
            for (int j = 0; j < actualColumns; ++j) {
                board[i][j] = ' ';  // All spaces
            }
        }
    }
}