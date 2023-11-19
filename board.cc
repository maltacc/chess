#include "board.h"
using namespace std; 

Board::Board() {}

void Board::clear() {}

void Board::place(char piece, Pos pos, int turn) {
    b[7 - pos.getRank()][pos.getFile()].addPiece(piece, turn);
    notifyObservers(); 
} 

void Board::remove(Pos p) {
    if (!b[p.getRank()][p.getFile()].isEmpty()) { // remove if piece is present
        b[p.getRank()][p.getFile()].setEmpty(); 
        notifyObservers(); 
    }
}

bool Board::isValidMove(Move m) {
    
}

void Board::move(Move m) {
    if (isValidMove(m)) {
        b[m.getStart().getRank()][m.getStart().getFile()].move(b[m.getEnd().getRank()][m.getEnd().getFile()]);
    }
    // move is invalid
}

void Board::attach(Observer* o) { observers.emplace_back(o); }

void Board::notifyObservers() {
    for (auto o: observers) o->notify(*this); 
}

char Board::getPiece(int r, int c) { return b[r][c].getPiece(); }

Board::~Board() {}
