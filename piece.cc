# include "piece.h"
using namespace std; 

Piece::Piece(Type t, Side s): type{t}, side{s} {}

Piece::Piece(char piece, Side s): side{s} {
    char p = toupper(piece); 
    if (piece == 'K') type = Type::K; 
    else if (piece == 'Q') type = Type::Q; 
    else if (piece == 'N') type = Type::N; 
    else if (piece == 'B') type = Type::B;
    else if (piece == 'P') type = Type::P; 
    else if (piece == 'R') type = Type::R; 
}

Type Piece::getType() const { return type; }

Side Piece::getSide() const { return side; }

bool Piece::operator==(const Piece &other) const{
    return type == other.type && side == other.side;
}
