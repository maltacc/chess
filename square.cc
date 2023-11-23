#include "square.h"
using namespace std; 

Square::Square() {} 

Square::Square(Piece *p): p{p} {}

void Square::move(Square &s) {
    std::swap(p, s.p); 
    delete p;
    p = nullptr; 
}

bool Square::isEmpty() const { return p == nullptr; }

void Square::setEmpty() const { 
    if (p) {
        delete p;
        p = nullptr;
    }
}

void Square::addPiece(char piece) {
    if (p) delete p; 
    if (piece >= 'a' && piece <= 'z') p = new Piece{piece, Side::B};
    else p = new Piece{piece, Side::W}; 
}

void Square::setAttacked(bool val) { attacked = 0; }

Piece& Square::operator*() const { return *p; }

bool Square::isAttacked() const { return attacked; }
Square::~Square() { delete p; }
