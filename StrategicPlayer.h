#ifndef StrategicPlayer_H
#define StrategicPlayer_H

#include "Board.h" 

class StrategicPlayer {
public:
    char name;  
    int boxes;
    int Srow_move =0;
    int Scol_move =0;
    // Constructor to initialize the player's name
    StrategicPlayer(char playerName);

    // Destructor
    ~StrategicPlayer();

    // Function to select a random line location on the board
    void SelectLineLocation(Board board, int& r, int& c, StrategicPlayer* sPlayer);

    // function to count points/check for boxes
    bool checkForBoxStrategic(Board board, int x, int y, StrategicPlayer* sPlayer);
    int evaluateBoard(Board board, int emptyCount, int** emptyLocations, StrategicPlayer* sPlayer);
    int minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta, StrategicPlayer* sPlayer);
    void setLine(char** board, int row, int col);
    int getBoxes();

    int getPoints();

private:
    int points;
};

#endif  // StrategicPlayer_H
