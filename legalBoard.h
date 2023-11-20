#ifndef __LEGALBOARD_H__
#define __LEGALBOARD_H__
#include "board.h"
#include <vector>
using namespace std;

class LegalBoard: public Board {
    struct Castle { // struct to keep track of castling rights
        bool blackKing = true; // Black king-side castle
        bool blackQueen = true; // Black queen-side castle
        bool whiteKing = true; // White king-side castle
        bool whiteQueen = true; // White queen-side castle
    };

    Side turn;
    bool whiteCheck, blackCheck;
    vector<Move> legalMoves;
    Castle castle{};

    // Updates the legal moves for pieces matching Side turn.
    // Uses the following 6 fns to update the legal moves for all the pieces.
    void updateLegalMoves();

    // Calculates legal moves for specific piece types at specific positions.
    // Adds legal moves to legalMoves as well as to squares at Pos p.
    void updateKing(Pos p);
    void updateQueen(Pos p);
    void updateRook(Pos p);
    void updateBishop(Pos p);
    void updateKnight(Pos p);
    void updatePawn(Pos p);

    // Calculates if there is a draw by insufficient material.
    bool insufficientMaterial();

    // Calculates if there have been three moves in a row made by the same player. 
    // bool threefoldRepetition();

    // Updates if the game is in checkmate, stalemate, draw, still active, or none.
    void updateState();
    
    public:
        Side getTurn();
        bool move(Move m) override;
        void promote(char piece); // Does nothing if there is no pawn to promote

        auto begin(); 
        auto end();

};

#endif
