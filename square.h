#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "piece.h"
#include "move.h"

class Square {
    Piece *p = nullptr; 
    int attacked = 0; // square is attacked

    public: 
        const Piece * piece();
        Square();
        Square(Piece *p); 
        void move(Square &s); // move piece to s, handles captures too
        void setEmpty(); // remove piece from square
        bool isEmpty() const; // square doesn't contain a piece
        void addPiece(Piece piece); // add piece to square
        void setAttacked(int i);
        void addAttacked(); 
        bool isAttacked() const; // square is under attack
        int attackCount();
        ~Square(); 
}; 

#endif 
