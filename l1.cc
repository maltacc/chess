#include "l1.h"
#include <vector>
using namespace std; 

L1::L1(LegalBoard *b): Computer{b} {}

Move L1::getMove() {
    // tmp will never be empty (checkmate) because the Game checks
    // for it before calling getMove()
    vector<Move> tmp = b->getLegalMoves();  
    srand(time(NULL)); 
    return tmp[rand() % tmp.size()]; 
}

L1::~L1() { delete b; }
