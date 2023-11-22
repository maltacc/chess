#ifndef __MOVE_H__
#define __MOVE_H__
#include "pos.h"
#include "piece.h"

class Move {
    Pos start, end; 

    public: 
        Move(Pos start, Pos end); 
        Pos getStart(); 
        Pos getEnd(); 
}; 

#endif 
