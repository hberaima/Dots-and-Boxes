#ifndef BOARD_H
#define BOARD_H

#include <iostream>

class Board {
public:
    // Constructor and Destructor
    Board(int rows, int columns);
    ~Board();

    // Public member functions
    void printBoard() const;  // Print the board to the console
    char** getBoard();
    int GetAllEmptyLineLocations(int actualRows, int actualColumns, char** board, int** emptyLocations);
    int getRows();
    int getColumns();
    void setLine(int row, int col, char input);

private:
    // Private member variables
    int numRows, numCols;     // Dimensions of the board
    char** gameBoard;         // Pointer to 2D array representing the board

    // Private helper functions
    char** initialize_board(int rows, int columns);  // Initialize the board
};

#endif  // BOARD_H
