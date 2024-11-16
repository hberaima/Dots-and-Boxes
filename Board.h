#ifndef BOARD_H
#define BOARD_H

class Board {
public:
    char** gameBoard;  // Pointer to 2D board array
    int numRows, numCols;

    // Constructor to initialize the board
    Board(int rows, int columns);

    // Destructor to clean up dynamically allocated memory
    ~Board();

    // Function to initialize the board with alternating dots and spaces
    char** initialize_board(int rows, int columns);

    // Function to print the board
    void printBoard() const;
};

#endif  // BOARD_H
