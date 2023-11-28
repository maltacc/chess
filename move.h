#ifndef __MOVE_H__
#define __MOVE_H__
#include "pos.h"
#include "piece.h"

class Move {
    protected:
        Pos start, end; 
        Type promote = Type::P; // The promotion is pawn by default; illegal to promote to pawn.
                                // Pawn promotion signifies 

    public: 
        Move(Pos start, Pos end, bool enPassant = 0);
        Move(Pos start, Pos end, Type promote);
        Pos getStart() const;
        Pos getEnd() const;
        Type getPromo() const;
        bool isEnPassant() const;
        bool operator==(const Move &other) const;
}; 

#endif 
