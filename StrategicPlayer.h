#ifndef StrategicPlayer_H
#define StrategicPlayer_H

#include "Board.h" 

class StrategicPlayer {
public:
    char name;  
    int boxes;
    // Constructor to initialize the player's name
    StrategicPlayer(char playerName);

    // Destructor
    ~StrategicPlayer();

    // Function to select a random line location on the board
    void SelectLineLocation(int actualRows, int actualColumns, char** board, int emptyLocations[][2], int emptyCount, char playername);

    // function to count points/check for boxes
    bool checkForBoxStrategic(char** board, int x, int y, char player, int rows, int columns, StrategicPlayer* StrategicPlayer);
    
    int getPoints();

private:
    int points;
};

#endif  // StrategicPlayer_H
