#include "pos.h"
using namespace std; 

Pos::Pos(): rank{0}, file{0} {} 

Pos::Pos(string p) {
    rank = '8' - p[1]; // convert char to int, account for board indices
    file = p[0] - 'a'; 
}

Pos::Pos(int x, int y): rank{x}, file{y} {}

int Pos::getRank() { return rank; }

int Pos::getFile() { return file; }

bool Pos::operator!=(const Pos &other) {
    return !(*this <=> other); 
}

Pos::~Pos() {}
