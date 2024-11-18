#include "StrategicPlayer.h"
#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding random numbers
using namespace std;


// Constructor: Initializes the player's name
StrategicPlayer::StrategicPlayer(char playerName) : name(playerName) {
    
}

// Destructor: Clean up (empty as no dynamic memory is used)
StrategicPlayer::~StrategicPlayer() { }



// Select a random line location
void StrategicPlayer::SelectLineLocation(int actualRows, int actualColumns, char** board, int** emptyLocations, int emptyCount, char playername) { 
    if (emptyCount == 0) {
        return;
    }
    srand(time(nullptr));
    // Select a random empty spot
    int randomIndex = rand() % emptyCount;  // Get a random index using custom_rand
    Srow_move = emptyLocations[randomIndex][0];
    Scol_move = emptyLocations[randomIndex][1];

    // Place the specified character in the selected spot
    board[Srow_move][Scol_move] = tolower(playername);

    // Print a move
    std::cout <<playername << " " <<Srow_move << " " << Scol_move << std::endl;

}

bool StrategicPlayer::checkForBoxStrategic(char** board, int x, int y, char player, int rows, int columns, StrategicPlayer* strategicPlayer) {
    bool boxCompleted = false;

    // Horizontal line case (top or bottom of the box)
    if (x % 2 == 0 && y % 2 == 1) {
        // Check above for a box
        if (x > 0 &&
            board[x - 1][y - 1] != ' ' &&  // Left vertical line
            board[x - 1][y + 1] != ' ' &&  // Right vertical line
            board[x - 2][y] != ' ') {      // Top horizontal line
            // Top box is completed
            board[x - 1][y] = toupper(player);  // Place the player's symbol in the box
            strategicPlayer->boxes++;
            strategicPlayer->points++;         // Add a point for the completed box
            boxCompleted = true;
        }

        // Check below for a box
        if (x < rows - 1 &&
            board[x + 1][y - 1] != ' ' &&  // Left vertical line
            board[x + 1][y + 1] != ' ' &&  // Right vertical line
            board[x + 2][y] != ' ') {      // Bottom horizontal line
            // Bottom box is completed
            board[x + 1][y] = toupper(player);  // Place the player's symbol in the box
            strategicPlayer->boxes++;
            strategicPlayer->points++;         // Add a point for the completed box
            boxCompleted = true;
        }
    }
    // Vertical line case (left or right of the box)
    else if (y % 2 == 0 && x % 2 == 1) {
        // Check to the left for a box
        if (y > 0 &&
            board[x - 1][y - 1] != ' ' &&  // Top horizontal line
            board[x + 1][y - 1] != ' ' &&  // Bottom horizontal line
            board[x][y - 2] != ' ') {      // Left vertical line
            // Left box is completed
            board[x][y - 1] = toupper(player);  // Place the player's symbol in the box
            strategicPlayer->boxes++;
            strategicPlayer->points++;         // Add a point for the completed box
            boxCompleted = true;
        }

        // Check to the right for a box
        if (y < columns - 1 &&
            board[x - 1][y + 1] != ' ' &&  // Top horizontal line
            board[x + 1][y + 1] != ' ' &&  // Bottom horizontal line
            board[x][y + 2] != ' ') {      // Right vertical line
            // Right box is completed
            board[x][y + 1] = toupper(player);  // Place the player's symbol in the box
            strategicPlayer->boxes++;
            strategicPlayer->points++;         // Add a point for the completed box
            boxCompleted = true;
        }
    }

    return boxCompleted;
}

    

int StrategicPlayer::getPoints()
{
    return points;
}