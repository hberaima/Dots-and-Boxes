#include "Board.h"
#include <iostream>
using namespace std;

// Constructor: Initializes the board with the given dimensions
Board::Board(int rows, int columns) : numRows(rows), numCols(columns) {
    gameBoard = initialize_board(rows, columns);  // Allocate memory and initialize the board
}

// Destructor: Frees dynamically allocated memory for the board
Board::~Board() {
    // Clean up dynamically allocated memory
    for (int i = 0; i < numRows; ++i) {
        delete[] gameBoard[i];  // Free each row
    }
    delete[] gameBoard;  // Free the main board array
}

// Function to initialize the board with alternating dots and spaces
char** Board::initialize_board(int rows, int columns) {
    char** board = new char*[rows];  // Allocate memory for rows
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns];  // Allocate memory for columns in each row
        if (i % 2 == 0) {  // Rows with dots and spaces
            for (int j = 0; j < columns; ++j) {
                board[i][j] = (j % 2 == 0) ? '.' : ' ';  // Dot in even columns, space in odd
            }
        } else {  // Rows with spaces
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';  // All spaces
            }
        }
    }
    return board;  // Return the initialized board
}

// Function to print the board with row and column indices
void Board::printBoard() const {
    cout << "   ";
    for (int j = 0; j < numCols; ++j) {
        cout << j % 10;  // Print column indices
    }
    cout << endl;
    
    for (int i = 0; i < numRows; ++i) {
        cout << (i < 10 ? "0" : "") << i << " ";  // Print row indices
        for (int j = 0; j < numCols; ++j) {
            cout << gameBoard[i][j];  // Print board cells
        }
        cout << endl;
    }
}
