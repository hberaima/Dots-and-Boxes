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

    cin >> rows >> columns;
    if (rows < 2 || columns < 2) {
        cerr << "Error: Dots and Boxes requires at least 2 rows and 2 columns." << endl;
        throw runtime_error("Invalid board dimensions in the file.");
    }

    cin >> player1Char >> playerStatus >> player2Char;

       
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

        readInputFile("input1.txt", rows, columns, player1char, player2char, playerstatus);         // Read input file
        Board board = createBoard("input1.txt"); // Create the game board

        // Initialize empty locations

        int boardSize = board.getRows() * board.getColumns(); // number of maximum locations for board

        int** emptyLocations = new int*[boardSize];
        for (int i = 0; i < boardSize; ++i) {
            emptyLocations[i] = new int[2];
        }

        // Get all empty line locations
        int emptyCount = board.GetAllEmptyLineLocations(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations);

        // Setting up players
        RandomPlayer* RPlayer = nullptr;
        StrategicPlayer* SPlayer = nullptr;
        bool starter = false;
        setupPlayers(playerstatus, player1char, player2char, RPlayer, SPlayer, starter);

        // Main game loop //////////////////////////////////////////////
        cout << rows << " " << columns  << endl;
            while (emptyCount != 0) {
                RPlayer->SelectLineLocation(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations, emptyCount, RPlayer->name);
                emptyCount = board.GetAllEmptyLineLocations(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations);
                RPlayer->checkForBoxRandom(board.getBoard(), RPlayer->Rrow_move, RPlayer->Rcol_move, RPlayer->name, board.getRows(), board.getColumns(), RPlayer);
               
                SPlayer->SelectLineLocation(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations, emptyCount, SPlayer->name);
                emptyCount = board.GetAllEmptyLineLocations(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations);
                SPlayer->checkForBoxStrategic(board.getBoard(), SPlayer->Srow_move, SPlayer->Scol_move, SPlayer->name, board.getRows(), board.getColumns(), SPlayer);
            }

        // Print final board state
        std::cout << "END" <<std::endl<<std::endl;
        board.printBoard();
        std::cout << std::endl<<std::endl;
        // Sort players and determine winner

        if(SPlayer->boxes > RPlayer->boxes){
            if (SPlayer->name > RPlayer->name){
            std::cout << "Player " << RPlayer->name << " has " << RPlayer -> boxes<<"."<< std::endl;
            std::cout << "Player " << SPlayer->name << " has " << SPlayer -> boxes << " (win)."<< std::endl;
            }else{
                std::cout << "Player " << SPlayer->name << " has " << SPlayer -> boxes << " (win)."<< std::endl;
                std::cout << "Player " << RPlayer->name << " has " << RPlayer -> boxes<<"."<< std::endl;
            }
        }else if(SPlayer->boxes < RPlayer->boxes) {
            if (SPlayer->name > RPlayer->name){
            std::cout << "Player " << RPlayer->name << " has " << RPlayer -> boxes << " (win)."<< std::endl;
            std::cout << "Player " << SPlayer->name << " has " << SPlayer -> boxes<<"."<< std::endl;
            }else{
                std::cout << "Player " << SPlayer->name << " has " << SPlayer -> boxes<<"."<< std::endl;
                std::cout << "Player " << RPlayer->name << " has " << RPlayer -> boxes << " (win)."<< std::endl;
            }
        }else{
            if (SPlayer->name > RPlayer->name){
            std::cout << "Player " << RPlayer->name << " has " << RPlayer -> boxes << " (tie)."<< std::endl;
            std::cout << "Player " << SPlayer->name << " has " << SPlayer -> boxes << " (tie)."<< std::endl;
            }else{
                std::cout << "Player " << SPlayer->name << " has " << SPlayer -> boxes << " (tie)."<< std::endl;
                std::cout << "Player " << RPlayer->name << " has " << RPlayer -> boxes << " (tie)."<< std::endl;
        }

        


        // Clean up dynamically allocated memory
        for (int i = 0; i < boardSize; ++i) {
            delete[] emptyLocations[i];
        }
        delete[] emptyLocations;
        delete RPlayer;
        delete SPlayer;
        return 0;
        }
}
