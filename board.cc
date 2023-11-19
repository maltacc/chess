#include "board.h"
using namespace std; 

Board::Board() {}

void Board::clear() {}

void Board::place(Type p, Pos pos) {} 

void Board::remove(Pos &p) {
    if (!b[p.getRank()][p.getFile()].isEmpty()) // remove if piece is present
        b[p.getRank()][p.getFile()].setEmpty(); 
}

void Board::move(Pos start, Pos end) {} 

Board::~Board() {}
