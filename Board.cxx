
#include "Board.h"
#include <iostream>
using namespace std;

// Constructor: Initializes the board with the given dimensions
Board::Board(int rows, int columns) : numRows(rows), numCols(columns) {
    gameBoard = initialize_board(rows, columns);  // Allocate memory and initialize the board
}

// Destructor: Frees dynamically allocated memory for the board
Board::~Board() {
    // Clean up dynamically allocated memory
    for (int i = 0; i < numRows; ++i) {
        delete[] gameBoard[i];  // Free each row
    }
    delete[] gameBoard;  // Free the main board array
}

// Function to initialize the board with alternating dots and spaces
char** Board::initialize_board(int rows, int columns) {
    char** board = new char*[rows];  // Allocate memory for rows
    for (int i = 0; i < rows; ++i) {
        board[i] = new char[columns];  // Allocate memory for columns in each row
        if (i % 2 == 0) {  // Rows with dots and spaces
            for (int j = 0; j < columns; ++j) {
                board[i][j] = (j % 2 == 0) ? '.' : ' ';  // Dot in even columns, space in odd
            }
        } else {  // Rows with spaces
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';  // All spaces
            }
        }
    }
    return board;  // Return the initialized board
}

// Function to print the board with row and column indices
void Board::printBoard() const {
    // Print the X-axis tens indices
    std::cout << "    ";  // Leading space for alignment
    for (int col = 0; col < numCols; ++col) {
        if (col % 10 == 0) {
            std::cout << col / 10;  // Print tens place for column numbers
        } else {
            std::cout << " ";  // Space for non-tens place
        }
    }
    std::cout << std::endl;

    // Print the X-axis ones indices
    std::cout << "    ";  // Leading space for alignment
    for (int col = 0; col < numCols; ++col) {
        std::cout << col % 10;  // Print ones place for column numbers
    }
    std::cout << std::endl;

    // Print the game board with Y-axis indices
    for (int row = 0; row < numRows; ++row) {
        // Print Y-axis tens place
        if (row % 10 == 0) {
            std::cout << row / 10;
        } else {
            std::cout << " ";
        }

        // Print Y-axis ones place
        std::cout << row % 10 << " ";

        // Print the board's content
        for (int col = 0; col < numCols; ++col) {
            if (gameBoard[row][col] == '\0') {
                std::cout << " ";  // Empty space for uninitialized cells
            } else {
                std::cout << gameBoard[row][col];  // Print the actual board content
            }
        }
        std::cout << std::endl;
    }
}


int Board::GetAllEmptyLineLocations(int actualRows, int actualColumns, char** board, int** emptyLocations) { 
    int count = 0;
    
    // Traverse the board to find empty spots (assuming empty is represented by ' ')
    for (int i = 0; i < actualRows; i+=1) {
        if (i % 2 == 0) {
            for (int j = 0; j < actualColumns; ++j) {
            if (board[i][j] == ' ') {  // Empty spot is represented by space ' '
                emptyLocations[count][0] = i;  // Store the row index
                emptyLocations[count][1] = j;  // Store the column index
                ++count;  // Increment the count of empty spots
            }
        }
        }
        else{
            for (int j = 0; j < actualColumns; j+=2) {
            if (board[i][j] == ' ') {  // Empty spot is represented by space ' '
                emptyLocations[count][0] = i;  // Store the row index
                emptyLocations[count][1] = j;  // Store the column index
                ++count;  // Increment the count of empty spots
            }
        }
        }
        
    }

    return count;  // Return the number of empty spots
}

char** Board::getBoard() { return gameBoard;}
int Board::getRows() { return numRows;}
int Board::getColumns() {return numCols;}