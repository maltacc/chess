#ifndef __LEGALBOARD_H__
#define __LEGALBOARD_H__
#include "board.h"
#include <vector>
using namespace std;

class LegalBoard: public Board {
    struct Active {
        bool bkRook = false;
        bool bqRook = false;
        bool wkRook = false;
        bool wqRook = false;
        bool bKing = false;
        bool wKing = false;
    };

    Side turn;
    bool whiteCheck, blackCheck;
    vector<Move> legalMoves;
    Active active{};

    void updateLegalMoves();
    void updateKing(Pos p);
    void updateQueen(Pos p);
    void updateRook(Pos p);
    void updateBishop(Pos p);
    void updateKnight(Pos p);
    void updatePawn(Pos p); 
    bool insufficientMaterial();
    void updateState();
    
    public:
        Side getTurn();
        bool move(Move m) override;
        void promote(char piece); // Does nothing if there is no pawn to promote

        auto begin(); 
        auto end(); 
        /*
            Add an iterator for the computer to traverse through legal moves
        */

};

#endif
