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

    //Function to copy main board
    void copyBoard(char **source, char **destination, int rows, int columns);

    // fuction to evaluate potential next move
    int evaluateMove(char **board, int rows, int columns, int depth, char player, int **emptyLocations, int emptyCount);

    // Function to select a random line location on the board
    void SelectLineLocation(int actualRows, int actualColumns, char** board, int** emptyLocations, int emptyCount, char playername);

    //function to count boxes
    int countBoxes(char **board, int rows, int columns, char player);

    // function to count points/check for boxes
    bool checkForBoxStrategic(char** board, int x, int y, char player, int rows, int columns, StrategicPlayer* StrategicPlayer);
    
    int getPoints();

private:

};

#endif  // StrategicPlayer_H
