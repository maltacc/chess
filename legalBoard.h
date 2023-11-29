#ifndef __LEGALBOARD_H__
#define __LEGALBOARD_H__
#include "board.h"
#include "consts.h"
using namespace std;

class LegalBoard: public Board {
 
    LegalBoard(const Board& other); // ctor 

// Move Legality
//----------
    // stores legal moves for 1 turn at a time
    vector<Move> legalMoves;
    // Stores position of piece we can take by en passant 
    // if there's no piece we can take by en passant, 
    // set variable to a square that's impossible for a pawn to be in
    // update legalMoves to include en passant
    Pos epMove;

    // Updates the legal moves for pieces matching Side turn.
    // Generates a vector of all pseudolegal moves using the following 6 fns,
    // then removes moves that are not strictly legal.
    void updateLegalMoves();

    // Calculates pseudolegal moves for specific piece types at specific positions.
    // Adds the moves to legalMoves, and then moves that have their own king in check
    // are deleted in updateLegalMoves.
    void updateKingMoves(Pos p);
    void updateQueenMoves(Pos p);
    void updateRookMoves(Pos p);
    void updateBishopMoves(Pos p);
    void updateKnightMoves(Pos p);
    void updatePawnMoves(Pos p);
//----------

// Helper methods for repeat code:
//----------
    // Checks if x and y are within the appropriate index boundaries of our chess board.
    bool inBounds(int x, int y);
    bool sameType(int rankIndex, int fileIndex, Type t);
    bool sameSide(int rankIndex, int fileIndex, Side s);

    bool addValidMoves(int r, int c, int i, int j); // return 1 if move added, otherwise 0
    void traverseDir(int r, int c, int rowDir, int colDir);

    void addDiagonals(int r, int c); 
    void addPerpendiculars(int r, int c); 
    void addKnightLeaps(int ri, int ci, int rf, int cf); 

    void attackDir(int r, int c, int rowDir, int colDir); 
//----------

// King Information + Gamestate Functions:
//----------
    struct canCastle { // struct to keep track of castling rights
        bool blackKing = true; // Black king-side castle
        bool blackQueen = true; // Black queen-side castle
        bool whiteKing = true; // White king-side castle
        bool whiteQueen = true; // White queen-side castle
    };

    canCastle castle;
    Pos whiteKing = Pos{4, 7}, blackKing = Pos{4, 0}; // Default values for default setup
    int kingAttackers = 0;

    // Checks if a square is under attack.
    bool underCheck(Pos p, Side s);

    // Calculates if there is a draw by insufficient material.
    bool insufficientMaterial();

    // Updates if the game is in checkmate, stalemate, draw, still active, or none.
    void updateState();

    // Generates the attack map of the current opponent's pieces for the purposes
    // of generating legal King moves.
    void generateAttackMap();

    // Checks if the current turn's King can be at a specific index.
    // Fn needs to be run after generateAttackMap().
    bool canKingBeHere(int rankIndex, int fileIndex);

    // Updates whether the current king is under check under whiteCheck / blackCheck,
    // the number of attackers the king has, runs generateAttackMap, and updates the
    // location of the king.
    void updateKingInfo();

    // Checks if the king is in check in the current position without creating an attack
    // map or using kingAttackers.
    bool isKingInCheck();
//----------

    // Determines if the square at rankIndex, fileIndex is pinned to the current
    // turn's king.
    // condition: must be run after the location of the king has been determined.
    // bool isPinned(int rankIndex, int fileIndex);
    
    public:
        LegalBoard();
        // The following 4 of the Big 5 will be used exclusively for copying/assigning 
        // temporary boards for the Players. Since we don't wan't to notify observers, 
        // we don't copy this field over
        LegalBoard(const LegalBoard &other); // copy ctor
        LegalBoard(LegalBoard &&other); // move ctor
        LegalBoard &operator=(const LegalBoard &other); // copy assignment operator
        LegalBoard &operator=(LegalBoard &&other); // move assignment operator

        Side getTurn();
        bool move(Move m) override;

        // Checks if the current player is under check.
        bool underCheck();
        
        void promote(Type piece); // Does nothing if there is no pawn to promote
        
        // Determines if the position that the user set up is valid or not.
        // e.g. Is there one king per team?
        bool isValidPosition();

        // Sets the game to InPlay if the position is valid.
        void activateGame();

        const vector<Move>& getLegalMoves();
        ~LegalBoard() noexcept;
};

#endif
