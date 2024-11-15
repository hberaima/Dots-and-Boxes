#include "Board.h"

Board::Board(int dots_in_rows, int dots_in_cols) {
    string** gameBoard = new string*[dots_in_rows];
    for (int i = 0; i < dots_in_rows; i++) {
        gameBoard[i] = new string[dots_in_cols];
        for (int j = 0; j < dots_in_cols; j++) {
            if ((i % 2 == 0) && (j % 2 == 0)) {
                gameBoard[i][j] = ".";
            } else {
                gameBoard[i][j] = " ";
            }
        }
    }
}

Board::~Board() {
    // Destructor implementation
}


void printBoard(string** board, int rows, int columns) { // Function to print board
    int counter = 1;
    cout << "   0";
    for (int i = 1; i < columns; i++) {
        if(i % 10 == 0) {
            cout << counter;
            counter++;
        }
        else {
            cout << " ";
        }
    }
    
        cout << endl << "   ";
    for (int j = 0; j < columns; j++) {
        cout << j % 10;
    }
    cout << endl;
    
    for (int i = 0; i < rows; i++) {
        cout << (i < 10 ? "0" : "") << i << " ";
        for (int j = 0; j < columns; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}
