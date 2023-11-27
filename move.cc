#include "move.h"
using namespace std; 

Move::Move(Pos start, Pos end): start{start}, end{end}, promote{Type::K} {}

Move::Move(Pos start, Pos end, Type promote): start{start}, end{end}, promote{promote} {}

Pos Move::getStart() { return start; }

Pos Move::getEnd() { return end; }

Type Move::getPromo() { return promote; }

bool Move::operator==(const Move &other) const {
    return !(start != other.start) && !(end != other.end) && promote == other.promote;
}
