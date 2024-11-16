#include "Board.h"
#include "RandomPlayer.h"
#include "StrategicPlayer.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Initialize Variables
    string playerstatus;
    char player1char;
    char player2char;
    int rows;
    int columns;
    bool gameOn = true;

    
    // Open file for the game inputs
    ifstream gamefile("input1.txt");

    // Check if the file was successfully opened
    if (!gamefile) {
        cerr << "Error: The file cannot be opened." << endl;
        return 1;
    }

    // Get the board size from the file
    gamefile >> rows >> columns;

    if (rows < 2) {
    cerr << "Error: Dots and Boxes requires at least 2 rows." << endl;
    return 1;
    }

    // Adjust grid dimensions
    int actualRows = rows * 2 - 1;  // Rows with dots and spaces
    int actualColumns = columns * 2 - 1; // Columns with dots and spaces



    // Creating the game board dynamically
    cout << "Create the game board" << endl;
    Board board(actualRows, actualColumns);

    // Dynamically allocate emptyLocations
    cout << "Allocating empty memory array" << endl;
    int** emptyLocations = new int*[emptyCount];
    for (int i = 0; i < emptyCount; ++i) {
    emptyLocations[i] = new int[2]; // Assuming 2 columns for row and column indices
}
    

    // Assign players

    gamefile >> player1char >> playerstatus >> player2char;

    bool starter = false;

    cout << "Initializing randomplayer pointer" << endl;     
    RandomPlayer* RPlayer = nullptr;
    cout << "Initializing strategic player..." << endl;
    StrategicPlayer* SPlayer = nullptr;

    cout << "Set player status for characters" << endl;
    if (playerstatus == "Random") {
        starter = true;
        RPlayer = new RandomPlayer(player1char);
        SPlayer = new StrategicPlayer(player2char);
    } else if (playerstatus == "Strategic") {
        starter = true;
        RPlayer = new RandomPlayer(player2char);
        SPlayer = new StrategicPlayer(player1char);
    } else {
        cout << "Can't determine Player. Check input." << endl;
    }

    // Get empty board location
    cout << "get empty board location" << endl;
    int emptyCount = board.GetAllEmptyLineLocations(actualRows, actualColumns, board.getBoard(), emptyLocations);

    // Main game loop
    cout << "Begin game loop" << endl;
    if (starter) {
        while (gameOn) {
            RPlayer->SelectLineLocation(actualRows, actualColumns, board.getBoard(), emptyLocations, emptyCount, RPlayer->name);
            break;
        }
    }

    board.printBoard();

    // Clean up dynamically allocated memory

// After use, ensure to deallocate
for (int i = 0; i < emptyCount; ++i) {
    delete[] emptyLocations[i];
}
delete[] emptyLocations;

    return 0;
}
