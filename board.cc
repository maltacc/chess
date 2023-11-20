#include "board.h"
using namespace std; 

Board::Board(): state{State::None}, turn{Side::W} {}

void Board::clear() {}

void Board::place(char piece, Pos pos) {
    b[pos.getRank()][pos.getFile()].addPiece(piece);
    notifyObservers(); 
} 

void Board::remove(Pos p) {
    if (!b[p.getRank()][p.getFile()].isEmpty()) { // remove if piece is present
        b[p.getRank()][p.getFile()].setEmpty(); 
        notifyObservers(); 
    }
}

bool Board::move(Move m) {
    b[m.getStart().getRank()][m.getStart().getFile()].move(b[m.getEnd().getRank()][m.getEnd().getFile()]);
    return true;
}

void Board::attach(Observer* o) { observers.emplace_back(o); }

void Board::notifyObservers() {
    for (auto o: observers) o->notify(*this); 
}

State Board::getState(){ return state; }

Side Board::getTurn() { return turn; }

void Board::setTurn(Side s) { turn = s; }

Board::~Board() {}
