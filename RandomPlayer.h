#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include "Board.h" 

class RandomPlayer {
public:
    char name;  
    int boxes;
    int Rrow_move=0;
    int Rcol_move=0;
    // Constructor to initialize the player's name
    RandomPlayer(char playerName);

    // Destructor
    ~RandomPlayer();

    // Function to select a random line location on the board
    void SelectLineLocation(int actualRows, int actualColumns, char** board, int** emptyLocations, int emptyCount, char playername);

    int getPoints();

    // function to count points/check for boxes
    bool checkForBoxRandom(char** board, int x, int y, char player, int rows, int columns, RandomPlayer* randomPlayer);


private:
    int points;
};

#endif  // RANDOMPLAYER_H
