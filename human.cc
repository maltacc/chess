#include "human.h"
using namespace std; 

Human::Human() {}

Move Human::getMove() {
    // get legal moves 
    vector<Move> legals = b->getLegalMoves(); 
    
    // check if user's move is valid 
    string cmd; 
    while (cin >> cmd) {
        if (cmd != "move") cout << "Invalid move command. Try again" << endl; 
        else {
            string start, end; 
            cin >> start >> end; 
            Pos startPos = Pos{start}, endPos = Pos{end}; 
            for (auto m: legals) {
                if (!(m.getStart() != startPos) && !(m.getEnd() != endPos)) return m; 
            }
        }
    }
}

Human::~Human() {}
