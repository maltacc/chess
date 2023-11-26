#include "game.h"
using namespace std; 

void Game::setPlayer(string player, Player *p) {
    if (player == "human") p = new Human; 
    else {
        int lvl = player.back(); 
        if (lvl == 1) p = new L1{&b};
        else if (lvl == 2) p = new L2{&b}; 
        else if (lvl == 3) p = new L3{&b}; 
        else p = new L4{&b}; 
    }
}

Game::Game(): p1{nullptr}, p2{nullptr}, whiteScore{0}, blackScore{0} {}

void Game::setupCustom(istream &in) {
    string cmd; // string instead of char so we can check for keyword "done"
    while (in >> cmd && cmd != "done") { // while in setup mode
        if (cmd == "+") {
            char piece; 
            string pos; 
            in >> piece >> pos;
            if (b.getTurn() == Side::W) b.place(Piece{piece, Side::W}, Pos{pos});
            else b.place(Piece{piece, Side::B}, Pos{pos});
        }
        else if (cmd == "-") {
            string pos; 
            cin >> pos; 
            b.remove(Pos{pos}); // remove piece from pos
        }
        else if (cmd == "=") {
            string side; 
            in >> side; 
            if (side == "white") b.setTurn(Side::W); 
            else b.setTurn(Side::B); 
        }
    }
}

void Game::setupDefault() {
    b.place(Piece{Type::K, Side::W}, Pos{"e1"});// set up Kings 
    b.place(Piece{Type::K, Side::B}, Pos{"e8"}); 

    b.place(Piece{Type::Q, Side::W}, Pos{"d1"}); // set up Queens
    b.place(Piece{Type::Q, Side::B}, Pos{"d8"}); 

    b.place(Piece{Type::B, Side::W}, Pos{"f1"}); // set up Bishops
    b.place(Piece{Type::B, Side::W}, Pos{"c1"});
    b.place(Piece{Type::B, Side::B}, Pos{"f8"}); 
    b.place(Piece{Type::B, Side::B}, Pos{"c8"});

    b.place(Piece{Type::R, Side::W}, Pos{"a1"}); // set up Rooks
    b.place(Piece{Type::R, Side::W}, Pos{"h1"}); 
    b.place(Piece{Type::R, Side::B}, Pos{"a8"}); 
    b.place(Piece{Type::R, Side::B}, Pos{"h8"}); 

    b.place(Piece{Type::N, Side::W}, Pos{"b1"}); // set up Knights
    b.place(Piece{Type::N, Side::W}, Pos{"g1"});
    b.place(Piece{Type::N, Side::B}, Pos{"b8"});
    b.place(Piece{Type::N, Side::B}, Pos{"g8"});

    for (int i = 0; i < 7; i++) {
        b.place(Piece{Type::P, Side::W}, Pos{6, i}); // place white pawns
        b.place(Piece{Type::P, Side::B}, Pos{1, i}); // place black pawns
    }
}

int Game::run(string player1, string player2) {
    setPlayer(player1, p1, Side::W); 
    setPlayer(player2, p2, Side::B);
}

Game::~Game() {
    delete p1; 
    delete p2; 
}
