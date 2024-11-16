#include "RandomPlayer.h"
#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding random numbers
using namespace std;

// Constructor: Initializes the player's name
RandomPlayer::RandomPlayer(char playerName) : name(playerName), points(0) {
    int points = 0;
}

// Destructor: Clean up (empty as no dynamic memory is used)
RandomPlayer::~RandomPlayer() {
}

// Select a random line location
void RandomPlayer::SelectLineLocation(int actualRows, int actualColumns, char** board, int** emptyLocations, int emptyCount, char playername) {
      if (emptyCount == 0) {
        std::cout << "No empty spots available!" << std::endl;
        return;
    }

    cout << "Selecting Line Location" << endl;
    srand(time(nullptr));
    // Select a random empty spot
    int randomIndex = rand() % emptyCount;  // Get a random index using custom_rand
    int row = emptyLocations[randomIndex][0];
    int col = emptyLocations[randomIndex][1];

    // Place the specified character in the selected spot
    board[row][col] = tolower(playername);

    // Print a move
    std::cout <<playername << " " <<row << " " << col << std::endl;

    cout << "Done Selecting Line Location" << endl;

}

int RandomPlayer::getPoints() {
    return points;
}
