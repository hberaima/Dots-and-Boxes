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
void StrategicPlayer::SelectLineLocation(int actualRows, int actualColumns, char** board, int emptyLocations[][2], int emptyCount, char playername) { }

int StrategicPlayer::getPoints() {
    return points; 
}