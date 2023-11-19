#ifndef __MOVE_H__
#define __MOVE_H__
#include "pos.h"
#include "piece.h"

class Move {
    Pos start, end; 
    // Piece* captured = nullptr; // piece captured

    public: 
        Move(Pos start, Pos end); 
}; 

#endif 
