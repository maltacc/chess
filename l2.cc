#include "l2.h"
using namespace std; 

L2::L2(LegalBoard *b): Computer{b} {}

Move L2::getMove() {
    vector<Move> tmp = b->getLegalMoves(), favored;
    srand(time(NULL)); 

    // copy board contents over to a temporary board, 
    // which we'll use to test moves
    LegalBoard tmpBoard = LegalBoard{*b}; 

    // TO-DO: Find a way to simulate a move on a board. 
    // We want to see if making a move puts the opp in check
    // TO-DO: Find a way to undo our move to try the next move

    for (auto m: tmp) {
        int xf = m.getEnd().getRank(), yf = m.getEnd().getFile(); 
        // capturing move if ending position of move is on an
        // opponent's piece. By design, if the move is in valid
        // moves and the piece is occupied, it must be an enemy piece

        // check move if ending position puts opponent in check
        if (!b->getPiece(xf, yf) || 
            (tmpBoard.move(m) && tmpBoard.underCheck())) 
            favored.push_back(m); 

        resetMove();
    }

    // randomly choose a move from favored moves
    // if there are no check or capture moves available, return a random move
    int l = favored.size(); 
    return l ? favored[rand() % l] : tmp[rand() % tmp.size()]; 
}

L2::~L2() {}
