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

    Board(int dots_in_rows, int dots_in_cols);
    ~Board();

    char& operator()(int row,int col);
    // Member Functions
    int GetAllEmptyLineLocations(int* empty_rows, int* empty_cols) const;
    string determineTurn();
    string** createBoard(int rows, int columns);
    
private:
    // Member variables
    string** gameBoard;
    string currentPlayer;
    void printBoard(string** board, int rows, int columns);
};

#endif // HEADER_GUARD