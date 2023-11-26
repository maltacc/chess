#include "l3.h"
using namespace std; 

L3::L3(LegalBoard *b): Computer{b} {}

Move L3::getMove() {
    vector<Move> tmp = b->getLegalMoves(), favored;
    srand(time(NULL)); 

    // avoid getting captured by checking if square is attacked 
    /* TO-DO: Alan */

    LegalBoard tmpBoard = LegalBoard{*b}; 

    for (auto m: tmp) {
        int xf = m.getEnd().getRank(), yf = m.getEnd().getFile(); 
        if (!b->getPiece(xf, yf) || 
            (tmpBoard.move(m) && tmpBoard.underCheck())) 
            favored.push_back(m); 

        tmpBoard = LegalBoard{*b};
    }

    int l = favored.size(); 
    return l ? favored[rand() % l] : tmp[rand() % tmp.size()]; 
}

L3::~L3() {}
