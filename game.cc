#include "game.h"
using namespace std; 

void Game::setPlayer(string player, Player *p, Side s) {
    if (player == "human") p = new Human; 
    else {
        int lvl = player.back(); 
        if (lvl == 1) p = new L1{s, &b};
        else if (lvl == 2) p = new L2{s, &b}; 
        else if (lvl == 3) p = new L3{s, &b}; 
        else p = new L4{s, &b}; 
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
            b.place(piece, Pos{pos});
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
    b.place('K', Pos{"e1"});// set up Kings 
    b.place('k', Pos{"e8"}); 

    b.place('Q', Pos{"d1"}); // set up Queens
    b.place('q', Pos{"d8"}); 

    b.place('B', Pos{"f1"}); // set up Bishops
    b.place('B', Pos{"c1"});
    b.place('b', Pos{"f8"}); 
    b.place('b', Pos{"c8"});

    b.place('R', Pos{"a1"}); // set up Rooks
    b.place('R', Pos{"h1"}); 
    b.place('r', Pos{"a8"}); 
    b.place('r', Pos{"h8"}); 

    b.place('N', Pos{"b1"}); // set up Knights
    b.place('N', Pos{"g1"});
    b.place('n', Pos{"b8"});
    b.place('n', Pos{"g8"});

    for (int i = 0; i < 7; i++) {
        b.place('P', Pos{6, i}); // place white pawns
        b.place('p', Pos{1, i}); // place black pawns
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
