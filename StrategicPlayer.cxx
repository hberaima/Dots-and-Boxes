#include "StrategicPlayer.h"
#include "Board.h"
#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding random numbers
#include <limits>
using namespace std;

// Constructor: Initializes the player's name
StrategicPlayer::StrategicPlayer(char playerName) : name(playerName) {}

// Destructor: Clean up (empty as no dynamic memory is used)
StrategicPlayer::~StrategicPlayer() { }

int StrategicPlayer::evaluateBoard(Board board, int emptyCount, int** emptyLocations, StrategicPlayer* sPlayer) {
    int score = 0;

    for (int i = 0; i < emptyCount; ++i) {
        int row = emptyLocations[i][0];
        int col = emptyLocations[i][1];

        if (row < 0 || row >= board.getRows() || col < 0 || col >= board.getColumns()) {
            continue; // Skip invalid indices
        }

        Board tempBoard = board; // Use copy constructor
        tempBoard.setLine(row, col, sPlayer->name);

        if (checkForBoxStrategic(tempBoard, row, col, sPlayer)) {
            score += 10;
        }
    }

    return score;
}


int StrategicPlayer::minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta, StrategicPlayer* sPlayer) {
    static int minimaxCalls = 0;
    int currentCall = ++minimaxCalls;
    
    std::cout << "Minimax call #" << currentCall << " (depth: " << depth << ", " 
              << (isMaximizing ? "maximizing" : "minimizing") << ")" << std::endl;

    int maxEmptyLocations = board.getRows() * board.getColumns();
    std::cout << "Minimax #" << currentCall << ": Allocating memory for " << maxEmptyLocations << " locations" << std::endl;

    // Dynamically allocate `emptyLocations`
    int** emptyLocations = new int*[maxEmptyLocations];
    for (int i = 0; i < maxEmptyLocations; ++i) {
        emptyLocations[i] = new int[2];
    }

    // Get all empty locations
    int emptyCount = board.GetAllEmptyLineLocations(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations);
    std::cout << "Minimax #" << currentCall << ": Found " << emptyCount << " empty locations" << std::endl;

    // Base case: No moves left or max depth reached
    if (emptyCount == 0 || depth == 0) {
        std::cout << "Minimax #" << currentCall << ": Reached base case" << std::endl;
        int evaluation = evaluateBoard(board, emptyCount, emptyLocations, sPlayer);
        
        // Clean up before return
        std::cout << "Minimax #" << currentCall << ": Cleaning up memory before base case return" << std::endl;
        for (int i = 0; i < maxEmptyLocations; ++i) {
            delete[] emptyLocations[i];
        }
        delete[] emptyLocations;
        
        return evaluation;
    }

    int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (int i = 0; i < emptyCount; ++i) {
        int r = emptyLocations[i][0];
        int c = emptyLocations[i][1];

        std::cout << "Minimax #" << currentCall << ": Testing move at (" << r << ", " << c << ")" << std::endl;
        
        // Make a move
        board.setLine(r, c, isMaximizing ? 'S' : 'R');

        // Recursive call
        int score = minimax(board, depth - 1, !isMaximizing, alpha, beta, sPlayer);
        std::cout << "Minimax #" << currentCall << ": Move (" << r << ", " << c << ") scored: " << score << std::endl;

        // Undo move
        board.setLine(r, c, ' ');

        // Update best score
        if (isMaximizing) {
            if (score > bestScore) {
                bestScore = score;
                std::cout << "Minimax #" << currentCall << ": New best max score: " << bestScore << std::endl;
            }
            if (bestScore > alpha) {
                alpha = bestScore;
            }
        } else {
            if (score < bestScore) {
                bestScore = score;
                std::cout << "Minimax #" << currentCall << ": New best min score: " << bestScore << std::endl;
            }
            if (bestScore < beta) {
                beta = bestScore;
            }
        }

        // Alpha-beta pruning
        if (beta <= alpha) {
            std::cout << "Minimax #" << currentCall << ": Pruning at alpha=" << alpha << ", beta=" << beta << std::endl;
            break;
        }
    }

    // Clean up
    std::cout << "Minimax #" << currentCall << ": Cleaning up memory before return" << std::endl;
    for (int i = 0; i < maxEmptyLocations; ++i) {
        delete[] emptyLocations[i];
    }
    delete[] emptyLocations;

    std::cout << "Minimax #" << currentCall << ": Returning score " << bestScore << std::endl;
    return bestScore;
}

void StrategicPlayer::SelectLineLocation(Board board, int& r, int& c, StrategicPlayer* sPlayer) {
    int maxEmptyLocations = board.getRows() * board.getColumns();
    int** emptyLocations = new int*[maxEmptyLocations];
    for (int i = 0; i < maxEmptyLocations; ++i) {
        emptyLocations[i] = new int[2];
    }

    int emptyCount = board.GetAllEmptyLineLocations(board.getRows(), board.getColumns(), board.getBoard(), emptyLocations);

     // Safety check to prevent out-of-bounds access
    if (emptyCount == 0) {
        r = -1;
        c = -1;
        
        // Clean up memory
        for (int i = 0; i < maxEmptyLocations; ++i) {
            delete[] emptyLocations[i];
        }
        delete[] emptyLocations;
        
        return;
    }

    int bestScore = std::numeric_limits<int>::min();

    for (int i = 0; i < emptyCount; ++i) {
        int currentRow = emptyLocations[i][0];
        int currentCol = emptyLocations[i][1];

        board.setLine(currentRow, currentCol, name);

        int moveScore = minimax(board, 3, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), sPlayer);

        board.setLine(currentRow, currentCol, ' ');

        if (moveScore > bestScore) {
            bestScore = moveScore;
            r = currentRow;
            c = currentCol;
        }
    }

    for (int i = 0; i < maxEmptyLocations; ++i) {
        delete[] emptyLocations[i];
    }
    delete[] emptyLocations;
}

bool StrategicPlayer::checkForBoxStrategic(Board board, int x, int y, StrategicPlayer* sPlayer) {
    if (x < 0 || x >= board.getRows() || y < 0 || y >= board.getColumns()) {
        return false;
    }

    // Only check for box completion on horizontal or vertical lines
    if (!(x % 2 == 0 && y % 2 == 1) && !(y % 2 == 0 && x % 2 == 1)) {
        return false;
    }

    bool boxCompleted = false;
    char** gameBoard = board.getBoard();

    // Horizontal line case
    if (x % 2 == 0 && y % 2 == 1) {
        // Check above for a box
        if (x > 1 && y > 0 && y < board.getColumns() - 1 &&
            gameBoard[x - 1][y - 1] != ' ' &&  // Left vertical line
            gameBoard[x - 1][y + 1] != ' ' &&  // Right vertical line
            gameBoard[x - 2][y] != ' ') {      // Top horizontal line
            gameBoard[x - 1][y] = toupper(sPlayer->name);
            sPlayer->boxes++;
            boxCompleted = true;
        }
        
        // Check below for a box
        if (x < board.getRows() - 2 && y > 0 && y < board.getColumns() - 1 &&
            gameBoard[x + 1][y - 1] != ' ' &&  // Left vertical line
            gameBoard[x + 1][y + 1] != ' ' &&  // Right vertical line
            gameBoard[x + 2][y] != ' ') {      // Bottom horizontal line
            gameBoard[x + 1][y] = toupper(sPlayer->name);
            sPlayer->boxes++;
            boxCompleted = true;
        }
    }
    // Vertical line case (left or right of the box)
    else if (y % 2 == 0 && x % 2 == 1) {
        // Check to the left for a box
        if (y > 1 && x > 0 && x < board.getRows() - 1 &&
            gameBoard[x - 1][y - 1] != ' ' &&  // Top horizontal line
            gameBoard[x + 1][y - 1] != ' ' &&  // Bottom horizontal line
            gameBoard[x][y - 2] != ' ') {      // Left vertical line
            gameBoard[x][y - 1] = toupper(sPlayer->name);
            sPlayer->boxes++;
            boxCompleted = true;
        }
        
        // Check to the right for a box
        if (y < board.getColumns() - 2 && x > 0 && x < board.getRows() - 1 &&
            gameBoard[x - 1][y + 1] != ' ' &&  // Top horizontal line
            gameBoard[x + 1][y + 1] != ' ' &&  // Bottom horizontal line
            gameBoard[x][y + 2] != ' ') {      // Right vertical line
            gameBoard[x][y + 1] = toupper(sPlayer->name);
            sPlayer->boxes++;
            boxCompleted = true;
        }
    }
    
    return boxCompleted;
}
int StrategicPlayer::getPoints() {return points;}
int StrategicPlayer::getBoxes() {return boxes;}