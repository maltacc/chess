#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "piece.h"
#include "move.h"
#include <vector>

class Square {
    Piece *p = nullptr; 
    vector<Move> validMoves; // tracks the valid moves for every square

    public: 
        Square();
        Square(Piece *p); 
        void move(Square &s); // move piece to s, handles captures too
        void setEmpty(); // remove piece from square
        bool isEmpty(); // square doesn't contain a piece
        void addPiece(char piece); // add piece to square
        vector<Move> getMoves(); // get valid moves
        ~Square(); 
}; 

#endif 
