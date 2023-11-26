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

int Piece::getValue() const {
    switch(type) {
        case Type::Q: return 9; 
        case Type::N: return 3; 
        case Type::B: return 3; 
        case Type::P: return 1; 
        case Type::R: return 5;
        default: return 0; 
    }
}

bool Piece::operator==(const Piece &other) const{
    return type == other.type && side == other.side;
}
