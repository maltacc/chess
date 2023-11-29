#include "l4.h"
#include <algorithm>
using namespace std; 

L4::L4(LegalBoard *b): Computer{b} {}

Move L4::getMove() {

    // Design: Pick the move with the highest value if we can capture. 
    // Else, pick any other favored move. If there are no favored moves, 
    // pick a random available move 

    vector<Move> tmp = b->getLegalMoves(), favored, capture;
    srand(time(NULL)); 

    // avoid getting captured by checking if square is attacked 
    /* TO-DO: Alan */

    LegalBoard tmpBoard = LegalBoard{*b}; 

    for (auto m: tmp) {
        int xf = m.getEnd().getRank(), yf = m.getEnd().getFile(); 
        if (!b->getPiece(xf, yf)) capture.push_back(m); 
        else if (tmpBoard.move(m) && tmpBoard.underCheck()) favored.push_back(m); 
        tmpBoard = LegalBoard{*b};
    }

    int max = 0, maxIndex = -1;
    for (size_t i = 0; i < capture.size(); i++) {
        Pos p = capture[i].getEnd(); 
        int curVal = (*b->getPiece(p.getRank(), p.getFile())).getValue();
        if (curVal > max) {
            maxIndex = i; 
            max = curVal; 
        }
    }

    if (maxIndex == -1) { // no capture moves are available
        int l = favored.size(); 
        return l ? favored[rand() % l] : tmp[rand() % tmp.size()]; 
    }
    return capture[maxIndex]; 
}

L4::~L4() {}
