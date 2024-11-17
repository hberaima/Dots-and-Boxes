#ifndef StrategicPlayer_H
#define StrategicPlayer_H

#include "Board.h" 

class StrategicPlayer {
public:
    char name;  

    // Constructor to initialize the player's name
    StrategicPlayer(char playerName);

    // Destructor
    ~StrategicPlayer();

    // Function to select a random line location on the board
    void SelectLineLocation(int actualRows, int actualColumns, char** board, int** emptyLocations, int emptyCount, char playername);

    int getPoints();

private:
    int points;
};

#endif  // StrategicPlayer_H
