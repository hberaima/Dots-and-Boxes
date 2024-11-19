#include "StrategicPlayer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <climits>
#include <algorithm>

using namespace std;

// Constructor
StrategicPlayer::StrategicPlayer(char playerName) : name(playerName), boxes(0), Srow_move(-1), Scol_move(-1) {}

// Destructor
StrategicPlayer::~StrategicPlayer() {}

// Copy the board state
void StrategicPlayer::copyBoard(char** source, char** destination, int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            destination[i][j] = source[i][j];
        }
    }
}

// Evaluate a move recursively using minimax algorithm
int StrategicPlayer::evaluateMove(char** board, int rows, int columns, int depth, char player, int** emptyLocations, int emptyCount) {

    // Base case: reached maximum depth or no moves left
    if (depth == 0 || emptyCount == 0) {
        return countBoxes(board, rows, columns, player);
    }

    int bestScore = (player == name) ? INT_MIN : INT_MAX;
    char opponent = (player == 'B') ? 'R' : 'B';

    // Try each possible move
    for (int i = 0; i < emptyCount; ++i) {
        int row = emptyLocations[i][0];
        int col = emptyLocations[i][1];
        
        // Skip invalid moves
        if (board[row][col] != ' ') continue;

        // Make move
        board[row][col] = tolower(player);
        int boxesBefore = boxes;
        bool completedBox = checkForBoxStrategic(board, row, col, player, rows, columns, this);
        
        // Create new empty locations array excluding current move
        int** newEmptyLocations = new int*[emptyCount - 1];
        int newIndex = 0;
        for (int j = 0; j < emptyCount; ++j) {
            if (j != i) {
                newEmptyLocations[newIndex] = new int[2];
                newEmptyLocations[newIndex][0] = emptyLocations[j][0];
                newEmptyLocations[newIndex][1] = emptyLocations[j][1];
                newIndex++;
            }
        }

        // If box was completed, player gets another turn
        int score;
        if (completedBox) {
            score = evaluateMove(board, rows, columns, depth - 1, player, newEmptyLocations, emptyCount - 1);
        } else {
            score = evaluateMove(board, rows, columns, depth - 1, opponent, newEmptyLocations, emptyCount - 1);
        }

        // Cleanup
        for (int j = 0; j < emptyCount - 1; ++j) {
            delete[] newEmptyLocations[j];
        }
        delete[] newEmptyLocations;

        // Undo move
        board[row][col] = ' ';
        boxes = boxesBefore;

        // Update best score
        if (player == name) {
            bestScore = max(bestScore, score);
        } else {
            bestScore = min(bestScore, score);
        }
    }

    return bestScore;
}

// Select best move using minimax evaluation
void StrategicPlayer::SelectLineLocation(int actualRows, int actualColumns, char** board, int** emptyLocations, int emptyCount, char playerName) {
    if (emptyCount == 0) return;

    int bestScore = INT_MIN;
    Srow_move = emptyLocations[0][0];
    Scol_move = emptyLocations[0][1];

    // Try each possible move
    for (int i = 0; i < emptyCount; ++i) {
        int row = emptyLocations[i][0];
        int col = emptyLocations[i][1];

        // Skip invalid moves
        if (board[row][col] != ' ') continue;

        // Make move
        board[row][col] = tolower(playerName);
        int boxesBefore = boxes;
        
        // Evaluate position
        int score = evaluateMove(board, actualRows, actualColumns, 2, playerName, emptyLocations, emptyCount);

        // Undo move
        board[row][col] = ' ';
        boxes = boxesBefore;

        // Update best move
        if (score > bestScore) {
            bestScore = score;
            Srow_move = row;
            Scol_move = col;
        }
    }

    // Make the best move
    board[Srow_move][Scol_move] = tolower(playerName);
    cout << playerName << " " << Srow_move << " " << Scol_move << endl;
}

// Count boxes owned by player
int StrategicPlayer::countBoxes(char** board, int rows, int columns, char player) {
    int count = 0;
    for (int i = 1; i < rows; i += 2) {
        for (int j = 1; j < columns; j += 2) {
            if (board[i][j] == toupper(player)) {
                count++;
            }
        }
    }
    return count;
}

// Check for completed boxes
bool StrategicPlayer::checkForBoxStrategic(char** board, int x, int y, char player, int rows, int columns, StrategicPlayer* StrategicPlayer) {
        bool boxCompleted = false;

        // Horizontal line case (top or bottom of the box)
        if (x % 2 == 0 && y % 2 == 1) {
            // Check above for a box
            if (x > 0 &&
                board[x - 1][y - 1] != ' ' &&  // Left vertical line
                board[x - 1][y + 1] != ' ' &&  // Right vertical line
                board[x - 2][y] != ' ') {      // Top horizontal line
                // Top box is completed
                board[x - 1][y] = toupper(player);  // Mark the box with the uppercase player symbol
                StrategicPlayer->boxes++;
                boxCompleted = true;
            }
            // Check below for a box
            if (x < rows - 1 &&
                board[x + 1][y - 1] != ' ' &&  // Left vertical line
                board[x + 1][y + 1] != ' ' &&  // Right vertical line
                board[x + 2][y] != ' ') {      // Bottom horizontal line
                // Bottom box is completed
                board[x + 1][y] = toupper(player);  // Mark the box with the uppercase player symbol
                StrategicPlayer->boxes++;
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
                board[x][y - 1] = toupper(player);  // Mark the box with the uppercase player symbol
                StrategicPlayer->boxes++;
                boxCompleted = true;
            }
            // Check to the right for a box
            if (y < columns - 1 &&
                board[x - 1][y + 1] != ' ' &&  // Top horizontal line
                board[x + 1][y + 1] != ' ' &&  // Bottom horizontal line
                board[x][y + 2] != ' ') {      // Right vertical line
                // Right box is completed
                board[x][y + 1] = toupper(player);  // Mark the box with the uppercase player symbol
                StrategicPlayer->boxes++;
                boxCompleted = true;
            }
        }
        return boxCompleted;
    }