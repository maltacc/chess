#ifndef __LEGALBOARD_H__
#define __LEGALBOARD_H__
#include "board.h"
#include <vector>
using namespace std;

class LegalBoard: public Board {
    struct canCastle { // struct to keep track of castling rights
        bool blackKing = true; // Black king-side castle
        bool blackQueen = true; // Black queen-side castle
        bool whiteKing = true; // White king-side castle
        bool whiteQueen = true; // White queen-side castle
    };

    Side turn;
    bool whiteCheck, blackCheck;
    vector<Move> legalMoves; // stores legal moves for 1 turn at a time
    canCastle castle{};

    // Updates the legal moves for pieces matching Side turn.
    // Uses the following 6 fns to update the legal moves for all the pieces.
    void updateLegalMoves();

    // Generates the attack map of the current opponent's pieces for the purposes
    // of generating legal King moves.
    void generateAttackMap();

    // Calculates legal moves for specific piece types at specific positions.
    // Adds legal moves to legalMoves as well as to squares at Pos p.
    void updateKingMoves(Pos p);
    void updateQueenMoves(Pos p);
    void updateRookMoves(Pos p);
    void updateBishopMoves(Pos p);
    void updateKnightMoves(Pos p);
    void updatePawnMoves(Pos p);

    bool inBounds(int x, int y); 

    void generateAttackMap(); 

    // Checks if a square is under attack.
    bool underCheck(Pos p, Side s);

    // Calculates if there is a draw by insufficient material.
    bool insufficientMaterial();

    // Calculates if there have been three moves in a row made by the same player. 
    bool threefoldRepetition();

    // Updates if the game is in checkmate, stalemate, draw, still active, or none.
    void updateState();

    // Helper methods: 
    void addDiagonals(int r, int c); 

    void addPerpendiculars(int r, int c); 

    void addKnightLeaps(int ri, int ci, int rf, int cf); 
    
    public:
        Side getTurn();
        bool move(Move m) override;
        void promote(char piece); // Does nothing if there is no pawn to promote

        auto begin(); 
        auto end();

};

#endif
