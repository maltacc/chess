# include "piece.h"
using namespace std; 

Piece::Piece(char t, Side s): type{t}, side{s} {}

char Piece::getType() { return type; }

Side Piece::getSide() { return side; }
