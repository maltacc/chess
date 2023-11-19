# include "piece.h"
using namespace std; 

Piece::Piece(Type t, Side s): type{t}, side{s} {
    if (type == Type::K) value = 0; // no capture value
    else if (type == Type::Q) value = 9; 
    else if (type == Type::B) value = 3; 
    else if (type == Type::N) value = 3; 
    else if (type == Type::R) value = 5; 
    else value = 1; 
}

Type Piece::getType() { return type; }

Side Piece::getSide() { return side; }
