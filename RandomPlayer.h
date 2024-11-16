#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include "Board.h" 

class RandomPlayer {
public:
    char name;  

    // Constructor to initialize the player's name
    RandomPlayer(char playerName);

    // Destructor
    ~RandomPlayer();

    // Function to select a random line location on the board
    void SelectLineLocation(int actualRows, int actualColumns, char** board, int emptyLocations[][2], int emptyCount, char playername);
};

#endif  // RANDOMPLAYER_H
