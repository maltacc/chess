#include "board.h"
#include "consts.h"
#include <string>
#include <array>
using namespace std; 

Board::Board(): state{State::None}, turn{Side::W} {}

Board::Board(const Board &other): state{other.state}, turn{other.turn} {
    // observers should be empty since we don't want to reflect changes
    
    for (int r = 0; r < DIM; r++) // copy Square array 
        for (int c = 0; c < DIM; c++) {
            b[r][c] = Square{other.b[r][c]}; // copies the square and piece in it
        }
}

Board::Board(Board &&other): state{other.state}, turn{other.turn} {
    // observers shouldn't be copied over because the big 5 are used to 
    // simulate valid moves, and we don't want observers to be notified 
    std::swap(b, other.b);
}

Board& Board::operator=(const Board &other) {
    if (this == &other) return *this; 
    Board tmp = other;
    std::swap(b, tmp.b); 
    std::swap(state, tmp.state); 
    std::swap(turn, tmp.turn); 
    return *this; 
}

Board& Board::operator=(Board &&other) {
    if (this == &other) return *this; 
    std::swap(state, other.state); 
    std::swap(turn, other.turn); 
    std::swap(b, other.b); 
    return *this; 
} 

void Board::clear() {
    for (int r = 0; r < DIM; r++)
        for (int c = 0; c < DIM; c++) b[r][c].setEmpty();
}

void Board::place(Piece piece, Pos pos) {
    b[pos.getRank()][pos.getFile()].addPiece(piece);
    notifyObservers({pos}); 
} 

void Board::remove(Pos p) {
    int r = p.getRank(), c = p.getFile(); 
    if (!b[r][c].isEmpty()) { // remove if piece is present
        b[r][c].setEmpty(); 
        notifyObservers({p}); 
    }
}

bool Board::move(Move m) {
    Pos start = m.getStart(), end = m.getEnd(); 
    b[start.getRank()][start.getFile()].move(b[end.getRank()][end.getFile()]);
    notifyObservers({start, end}); 
    return 1;
}

void Board::attach(Observer* o) { observers.emplace_back(o); }

void Board::notifyObservers(vector<Pos> v) {
    for (auto o: observers) o->notify(v, *this); 
}

const Piece* Board::getPiece(int i, int j) {
    return b[i][j].getPiece();
}

State Board::getState() { return state; }

Side Board::getTurn() { return turn; }

void Board::setTurn(Side s) { turn = s; }

Board::~Board() {}
