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

    bool whiteCheck, blackCheck;
    int kingAttackers = 0;
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
    void updateQueenMoves(Pos p, bool isPinned);
    void updateRookMoves(Pos p, bool isPinned);
    void updateBishopMoves(Pos p, bool isPinned);
    void updateKnightMoves(Pos p, bool isPinned);
    void updatePawnMoves(Pos p, bool isPinned);

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

    // Checks if the current turn's King can be at a specific index.
    // Fn needs to be run after generateAttackMap().
    bool canKingBeHere(int rank_index, int file_index);

    int kingAttackerCount();

    // Saves the location of the current King in either whiteKing or blackKing.
    void updateCurrentKingLocation();

    bool sameType(int rank_index, int file_index, Type t);

    bool sameSide(int rank_index, int file_index, Side s);

    // Determines if the square at rank_index, file_index is pinned to the current
    // turn's king.
    // condition: must be run after the location of the king has been determined.
    bool isPinned(int rank_index, int file_index);
    
    public:
        Side getTurn();
        bool move(Move m) override;
        void promote(Type piece); // Does nothing if there is no pawn to promote
        
        // Determines if the position that the user set up is valid or not.
        // e.g. Is there one king per team?
        bool isValidPosition();

        auto legalMovesBegin(); 
        auto legalMovesEnd();

};

#endif
