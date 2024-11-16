#include "Board.h"
#include "RandomPlayer.h"
#include "StrategicPlayer.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// g++ -ansi -pedantic -std=c++14 -Wall main.cxx Board.cxx RandomPlayer.cxx StrategicPlayer.cxx -o main

Board createBoard(string fileName) {
    int rows, columns;
    ifstream gamefile(fileName);

    if(!gamefile.is_open()) { 
        cerr << "Error: The file cannot be opened." << endl;
        throw runtime_error("Failed to open the file: " + fileName);
    }
        // Get the board size from the file
    gamefile >> rows >> columns;
    if (rows < 2) {
    cerr << "Error: Dots and Boxes requires at least 2 rows." << endl;
    throw runtime_error("Failed to open the file: " + fileName);
    }

    // Adjust grid dimensions
    int actualRows = rows * 2 - 1;  // Rows with dots and spaces
    int actualColumns = columns * 2 - 1; // Columns with dots and spaces

    Board board(actualRows, actualColumns);
    return board;
}

void readInputFile(const string& fileName, int& rows, int& columns, char& player1Char, char &player2Char, string& playerStatus) {
    ifstream gameFile(fileName);

    if(!gameFile.is_open()) {
        cerr << "Error: The file cannot be opened." << endl;
        throw runtime_error("Failed to open the file" + fileName);
    }

    gameFile >> rows >> columns;
    if (rows < 2 || columns < 2) {
        cerr << "Error: Dots and Boxes requires at least 2 rows and 2 columns." << endl;
        throw runtime_error("Invalid board dimensions in the file.");
    }

    gameFile >> player1Char >> playerStatus >> player2Char;

        if (gameFile.fail()) {
        cerr << "Error: Invalid player data in the input file." << endl;
        throw runtime_error("Failed to read player data from the file.");
    }

}

void setupPlayers(const string& playerstatus, char player1char, char player2char, RandomPlayer*& RPlayer, StrategicPlayer*& SPlayer, bool& starter) {
    if (playerstatus == "Random") {
        starter = true;
        RPlayer = new RandomPlayer(player1char);
        SPlayer = new StrategicPlayer(player2char);
    } else if (playerstatus == "Strategic") {
        starter = true;
        RPlayer = new RandomPlayer(player2char);
        SPlayer = new StrategicPlayer(player1char);
    } else {
        cerr << "Error: Can't determine player type. Check input." << endl;
        throw invalid_argument("Invalid player type in the input file.");
    }
}

int main() {
  // Initialize Variables
        int rows, columns;
        char player1char, player2char;
        string playerstatus;

        // Read input file
        cout << "reading input file... " << endl << endl;
        readInputFile("input1.txt", rows, columns, player1char, player2char, playerstatus);
        cout << "done reading input file" << endl;
        // Create the game board
        cout << "creating board using createBoard Func" << endl;
        Board board = createBoard("input1.txt");
        cout << "done." << endl << endl;

        // Initialize empty locations
        cout << "getting all empty line locations" << endl << endl;

        int maxEmptyLocations = board.getRows() * board.getColumns();
        int** emptyLocations = new int*[maxEmptyLocations];
        for (int i = 0; i < maxEmptyLocations; ++i) {
            emptyLocations[i] = new int[2];
        }

        // Get all empty line locations
        int emptyCount = board.GetAllEmptyLineLocations(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations);
        cout << "done." << endl << endl;

        // Set up players
        cout << "Setting up Players..." << endl << endl;
        RandomPlayer* RPlayer = nullptr;
        StrategicPlayer* SPlayer = nullptr;
        bool starter = false;
        setupPlayers(playerstatus, player1char, player2char, RPlayer, SPlayer, starter);
        cout << "done." << endl << endl;

        // Main game loop
        cout << "Starting the first loop..." << endl << endl;

        if (starter) {
            while (true) {
                RPlayer->SelectLineLocation(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations, emptyCount, RPlayer->name);
                break; // Placeholder for the game logic
            }
        }
        cout << "done." << endl << endl;

        // Print final board state
        cout << "Printing Board" << endl;
        board.printBoard();
        cout << "done." << endl << endl;

        // Clean up dynamically allocated memory
        for (int i = 0; i < maxEmptyLocations; ++i) {
            delete[] emptyLocations[i];
        }
        delete[] emptyLocations;

        delete RPlayer;
        delete SPlayer;

        return 0;

}
