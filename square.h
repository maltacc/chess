#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "piece.h"
#include "pos.h"
#include <vector>

class Square {
    Piece *p = nullptr; 
    vector<int> validMoves; // tracks the valid moves for every square
    Pos pos; 

    public: 
        Square(Pos pos); 
        Square(Piece *p, Pos pos); 
        void move(Square &s); // move piece to s, handles captures too
        void setEmpty(); // remove piece from square
        bool isEmpty(); // square doesn't contain a piece
        ~Square(); 
}; 

#endif 
