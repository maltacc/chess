#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "piece.h"
#include "move.h"

class Square {
    Piece *p = nullptr; 

    public: 
        friend class Board; 
        Square();
        Square(Piece *p); 
        void move(Square &s); // move piece to s, handles captures too
        void setEmpty(); // remove piece from square
        bool isEmpty(); // square doesn't contain a piece
        void addPiece(char piece); // add piece to square
        ~Square(); 
}; 

#endif 
