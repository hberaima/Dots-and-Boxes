// Project Name
// Author Name
// Date


#include "Board.h"
#ifndef HEADER_GUARD
#define HEADER_GUARD

class RandomPlayer {
public:
    char name;
    RandomPlayer();
    ~RandomPlayer();

    // Member functions
    void selectLineLocation(Board& board, int& r, int & c);

private:
    // Member variables
    int points;
    std::string name;
};

#endif // HEADER_GUARD