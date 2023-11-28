#include "move.h"
using namespace std; 

Move::Move(Pos start, Pos end, bool enPassant): start{start}, end{end}, promote{Type::P} {
    if (enPassant) promote = Type::K;
}

Move::Move(Pos start, Pos end, Type promote): start{start}, end{end}, promote{promote} {}

Pos Move::getStart() const { return start; }

Pos Move::getEnd() const { return end; }

Type Move::getPromo() const { return promote; }

bool Move::isEnPassant() const { return promote == Type::K; }

bool Move::operator==(const Move &other) const {
    return !(start != other.start) && !(end != other.end) && promote == other.promote;
}
