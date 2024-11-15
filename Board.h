// Project Name
// Author Name
// Date
#include <iostream>
#include <string>
using namespace std;

#ifndef _BOARD_
#define _BOARD_

class Board {
public:
    Board(int rows, int columns);
    ~Board();

    char& operator()(int row, int col);
    int GetAllEmptyLineLocations(int* empty_rows, int* empty_cols) const;
    string determineTurn();
    void printBoard() const;
    char** gameBoard;

private:
    int numRows;
    int numCols;
    string currentPlayer;

    char** createBoard(int rows, int columns);
};

#endif // _BOARD_
