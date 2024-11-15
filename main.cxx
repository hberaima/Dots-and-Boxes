//----------------------------------------------------------------------------------
// Name: Hamid Beraima
// Email: hab5491@psu.edu
// Class: CMPSC 330
// Homework 4
// Due Date: November 18, 2024
//
// Description: This program builds upon my previous dots and boxes assignment the program will read the
// game settsings then create a two player game of dots and boxes
//
// Acknowledgement:
// https://www.geeksforgeeks.org/doubly-linked-list-in-cpp/ -- Used as Refresher to create a Structure to hold player info
// https://stackoverflow.com/a/30387118
//-------------------------------------------------------------------------------------

//i love you
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// i dont love you
// i hate you
int main() {
///////////////////// Read input1.txt file and create game Board
// Initialize Variables
    int columns;
    int rows;

    string inputLine;
    
    cout << "Please enter the number of Rows and Columns in the format '3 8' (e.g., 3 rows and 8 columns): ";
    if (!(cin >> rows >> columns)) {
        cerr << "Error: Invalid input format." << endl;
        return 1;
    }
 /*   if(inputLine.length() != 3)    { // COME BACK TO THIS LATER FIX DOUBLE DIGIT ROW OR COLUMN
        cerr << "Error" << endl;
    }*/
    // Get Number of Rows and Columns
    


    if( rows < 2 ) {
        cerr << "Error: Dots and Boxes requires at least 2 rows." << endl;
        return 1;
    }

    rows = rows * 2 - 1;
    columns = columns * 2 - 1;
    
    char Player;
    string Playstyle;
    cout << "Please enter your Player Letter and Playstyle in the format 'B Random' (e.g Player B with a Random Playstyle)" << endl;
    if(!(cin >> Player >> Playstyle) ) {
        cerr << "Error: INVALID INPUT" << endl;
        return 1;
    }
    if(tolower(Player) == 'x' ) {
        cerr << "Sorry no player can be player 'X'" << endl;
    }




    printBoard(gameBoard, rows, columns);

    // Determine wether player has Random Dot Selection or Strategic

    

    // First player to show up goes first 

    // Program selects first/next player 
    // Player selects a place to add a line. 
        // (Players can not select unacceptable line locations)
        // (The Random player should select a random location using rand() )
    // Program writes the log to the console in the same format that last assignment had (B 1 0) for example
    // Repeat last three steps


    // Finally program draws final board and writes the number of boxes earned by each player.


    return 0;
}
