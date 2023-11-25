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

void Square::setEmpty() { 
    if (p) {
        delete p;
        p = nullptr;
    }
}

void Square::addPiece(Piece piece) {
    if (p) delete p; 
    p = new Piece{piece.getType(), piece.getSide()};
}

void Square::setAttacked(int i) { attacked = i; }

void Square::addAttacked() { attacked++; }

bool Square::isAttacked() const { return attacked; }

const Piece * Square::piece() { return p; };

Square::~Square() { delete p; }
