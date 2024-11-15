#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(int rows, int columns) : numRows(rows), numCols(columns) {
    gameBoard = createBoard(rows, columns);
}

Board::~Board() {
    // Clean up dynamically allocated memory
    for (int i = 0; i < numRows; ++i) {
        delete[] gameBoard[i];
    }
    delete[] gameBoard;
}

char** Board::createBoard(int rows, int columns) {
    char** board = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns];
        if (i % 2 == 0) {  // Rows with dots
            for (int j = 0; j < columns; ++j) {
                board[i][j] = (j % 2 == 0) ? '.' : ' ';  // Dot in even columns, space in odd
            }
        } else {  // Rows with spaces
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';  // All spaces
            }
        }
    }
    return board;
}


void Board::printBoard() const {
    cout << "   ";
    for (int j = 0; j < numCols; ++j) {
        cout << j % 10;  // Print column indices
    }
    cout << endl;
    
    for (int i = 0; i < numRows; ++i) {
        cout << (i < 10 ? "0" : "") << i << " ";  // Print row indices
        for (int j = 0; j < numCols; ++j) {
            cout << gameBoard[i][j];
        }
        cout << endl;
    }
}
