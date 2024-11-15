#include <iostream>
#include <fstream>
#include "RandomPlayer.h"
#include "StrategicPlayer.h"

int main (){

    // initialize variables 
    std::string playerstatus;
    char player1char;
    char player2char;
    int rows;
    int columns;


    // Open file for the game inputs
    std::ifstream gamefile("input1.txt");

    // Check if the file was successfully opened
    if (!gamefile) {
        std::cerr << "Error: The file cannot be opened." << std::endl;
        return 1;
    }

    // Get the board size from the file
    gamefile >> rows >> columns;

    // Validate the board dimensions
    if (rows <= 0 || columns <= 0) {
        std::cerr << "Error: Invalid board dimensions." << std::endl;
        return 1;
    }

    // Adjusting the size of the board for alternating dots and spaces
    int actualRows = 2 * rows;
    int actualColumns = ((2 * columns) - 1);

    // Creating the game board dynamically


    // assingn players 
    RandomPlayer RandomPlayer;
    StrategicPlayer StrategicPlayer;

    gamefile>>player1char>>playerstatus >> player2char;

    if (playerstatus=="Random"){
        RandomPlayer.name = player1char;
        StrategicPlayer.name = player2char;
    }else if (playerstatus=="Strategic"){
        RandomPlayer.name = player2char;
        StrategicPlayer.name = player1char;
    }
    
    // tester 
    std::cout<< "strategic player :" << StrategicPlayer.name<< "and "<< RandomPlayer.name<<std::endl;

    //main game loop 
    while (true) {
        std::cout << "enter is player "<<player1char<<"move";
        break;
    };


return 0;
}
