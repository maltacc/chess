#ifndef __MOVE_H__
#define __MOVE_H__
#include "pos.h"
#include "piece.h"

class Move {
    protected:
        Pos start, end; 
        Type promote = Type::P; // The promotion is pawn by default; illegal to promote to pawn.

    public: 
        Move(Pos start, Pos end);
        Move(Pos start, Pos end, Type promote);
        Pos getStart(); 
        Pos getEnd();
        Type getPromo();
        bool operator==(const Move &other) const;
}; 

#endif 
