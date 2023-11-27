#ifndef __LEGALBOARD_H__
#define __LEGALBOARD_H__
#include "board.h"
#include "consts.h"
using namespace std;

class LegalBoard: public Board {
    struct canCastle { // struct to keep track of castling rights
        bool blackKing = true; // Black king-side castle
        bool blackQueen = true; // Black queen-side castle
        bool whiteKing = true; // White king-side castle
        bool whiteQueen = true; // White queen-side castle
    };

    Pos whiteKing = Pos{4, 7}, blackKing = Pos{4, 0};
    int kingAttackers = 0;
    vector<Move> legalMoves; // stores legal moves for 1 turn at a time
    canCastle castle{};

    LegalBoard(const Board& other); // ctor 

    // Updates the legal moves for pieces matching Side turn.
    // Uses the following 6 fns to update the legal moves for all the pieces.
    void updateLegalMoves();

    // Calculates legal moves for specific piece types at specific positions.
    // Adds legal moves to legalMoves as well as to squares at Pos p.
    void updateKingMoves(Pos p);
    void updateQueenMoves(Pos p, bool isPinned);
    void updateRookMoves(Pos p, bool isPinned);
    void updateBishopMoves(Pos p, bool isPinned);
    void updateKnightMoves(Pos p, bool isPinned);
    void updatePawnMoves(Pos p, bool isPinned);

    bool inBounds(int x, int y);

    // Checks if a square is under attack.
    bool underCheck(Pos p, Side s);

    // Calculates if there is a draw by insufficient material.
    bool insufficientMaterial();

    // Updates if the game is in checkmate, stalemate, draw, still active, or none.
    void updateState();

    // Helper methods: 
    bool addValidMoves(int r, int c, int i, int j); // return 1 if move added, otherwise 0
    void traverseDir(int r, int c, int rowDir, int colDir);

    void addDiagonals(int r, int c); 
    void addPerpendiculars(int r, int c); 
    void addKnightLeaps(int ri, int ci, int rf, int cf); 

    void attackDir(int r, int c, int rowDir, int colDir); 

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

    vector<Pos> kingAttackerLocations();

    bool sameType(int rankIndex, int fileIndex, Type t);

    bool sameSide(int rankIndex, int fileIndex, Side s);

    // Determines if the square at rankIndex, fileIndex is pinned to the current
    // turn's king.
    // condition: must be run after the location of the king has been determined.
    bool isPinned(int rankIndex, int fileIndex);
    
    public:
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
