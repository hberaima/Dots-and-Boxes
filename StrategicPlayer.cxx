#include "StrategicPlayer.h"
#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding random numbers
using namespace std;

// Constructor: Initializes the player's name
StrategicPlayer::StrategicPlayer(char playerName) : name(playerName) {
    int points = 0;
}

// Destructor: Clean up (empty as no dynamic memory is used)
StrategicPlayer::~StrategicPlayer() { }

// Select a random line location
    void StrategicPlayer::SelectLineLocation(int actualRows, int actualColumns, char** board, int** emptyLocations, int emptyCount, char playername) {


      if (emptyCount == 0) {
        std::cout << "END" << std::endl;
        return;
    }

    srand(time(0));
    // Select a random empty spot

    int randomIndex = rand() % emptyCount;  // Get a random index using custom_rand
    int row = emptyLocations[randomIndex][0];
    int col = emptyLocations[randomIndex][1];

    // Place the specified character in the selected spot
    board[row][col] = tolower(playername);

    // Print a move
    std::cout <<playername << " " <<row << " " << col % 10<< std::endl;
    
} 

int StrategicPlayer::getPoints() {
    return points; 
}