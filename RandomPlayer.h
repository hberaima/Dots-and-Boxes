// Project Name
// Author Name
// Date


#include "Board.h"
#ifndef HEADER_GUARD
#define HEADER_GUARD

class RandomPlayer {
public:
    RandomPlayer();
    ~RandomPlayer();

    // Member functions
    void selectLineLocation(Board& board, int& r, int & c);

private:
    // Member variables
    int variable;
};

#endif // HEADER_GUARD