#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "piece.h"
#include "move.h"
#include <vector>

class Square {
    Piece *p = nullptr; 
    vector<Move> validMoves; // tracks the valid moves for every square

    public: 
        friend class Board;

        Square();
        Square(Pos pos); 
        Square(Piece *p, Pos pos); 
        void move(Square &s); // move piece to s, handles captures too
        void setEmpty(); // remove piece from square
        bool isEmpty(); // square doesn't contain a piece
        void addPiece(char piece, Side turn); // add piece to square
        char getPiece();
        ~Square(); 
}; 

#endif 
