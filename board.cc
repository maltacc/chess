#include "board.h"
#include "consts.h"
#include <string>
using namespace std; 

Board::Board(): state{State::None}, turn{Side::W} {}

Board::Board(const Board &other): state{other.state}, turn{other.turn} {
    // observers should be empty since we don't want to reflect changes
    // copy Square array 
    for (int r = 0; r < DIM; r++) 
        for (int c = 0; c < DIM; c++) {
            b[r][c] = Square{other.b[r][c]}; // copies the square and piece in it
        }
}

void Board::clear() {}

void Board::place(Piece piece, Pos pos) {
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
    notifyObservers(); 
    return 1;
}

void Board::attach(Observer* o) { observers.emplace_back(o); }

void Board::notifyObservers() {
    for (auto o: observers) o->notify(*this); 
}

const Piece * Board::getPiece(int i, int j) {
    return b[i][j].getPiece();
}

State Board::getState() { return state; }

Side Board::getTurn() { return turn; }

void Board::setTurn(Side s) { turn = s; }

Board::~Board() {}
