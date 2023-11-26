#include "square.h"
using namespace std; 

Square::Square() {} 

Square::Square(const Square &other):
    p{other.p ? new Piece{other.p->getType(), other.p->getSide()} : nullptr}, 
    attacked{other.attacked} {}

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

int Square::attackCount() {
    return attacked;
}

const Piece* Square::getPiece() const { return p; };

Square::~Square() { delete p; }
