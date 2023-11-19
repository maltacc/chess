#include "square.h"
using namespace std; 

Square::Square(Pos pos): p{nullptr}, pos{pos} {}

Square::Square(Piece *p, Pos pos): p{p}, pos{pos} {}

void Square::move(Square &s) {
    std::swap(p, s.p); 
    delete p;
    p = nullptr; 
}

bool Square::isEmpty() { return p == nullptr; }

void Square::setEmpty() { 
    if (p) {
        delete p;
        p = nullptr;
    }
}

Square::~Square() { delete p; }
