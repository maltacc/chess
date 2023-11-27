#include "game.h"
using namespace std; 

Game::Game(LegalBoard *b): b{b}, wp{nullptr}, bp{nullptr}, whiteScore{0}, blackScore{0} {}

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

void Game::printScore(ostream &out) {
    out << "Final Score: " << endl;
    out << "White: " << whiteScore << endl; 
    out << "Black: " << blackScore << endl; 
}

void Game::setupDefault() {
    b->place(Piece{Type::K, Side::W}, Pos{"e1"});// set up Kings 
    b->place(Piece{Type::K, Side::B}, Pos{"e8"}); 

    b->place(Piece{Type::Q, Side::W}, Pos{"d1"}); // set up Queens
    b->place(Piece{Type::Q, Side::B}, Pos{"d8"}); 

    b->place(Piece{Type::B, Side::W}, Pos{"f1"}); // set up Bishops
    b->place(Piece{Type::B, Side::W}, Pos{"c1"});
    b->place(Piece{Type::B, Side::B}, Pos{"f8"}); 
    b->place(Piece{Type::B, Side::B}, Pos{"c8"});

    b->place(Piece{Type::R, Side::W}, Pos{"a1"}); // set up Rooks
    b->place(Piece{Type::R, Side::W}, Pos{"h1"}); 
    b->place(Piece{Type::R, Side::B}, Pos{"a8"}); 
    b->place(Piece{Type::R, Side::B}, Pos{"h8"}); 

    b->place(Piece{Type::N, Side::W}, Pos{"b1"}); // set up Knights
    b->place(Piece{Type::N, Side::W}, Pos{"g1"});
    b->place(Piece{Type::N, Side::B}, Pos{"b8"});
    b->place(Piece{Type::N, Side::B}, Pos{"g8"});

    for (int i = 0; i < DIM; i++) {
        b->place(Piece{Type::P, Side::W}, Pos{6, i}); // place white pawns
        b->place(Piece{Type::P, Side::B}, Pos{1, i}); // place black pawns
    }
}

void Game::run(string wplayer, string bplayer) {
    setPlayer(wplayer, wp);
    setPlayer(bplayer, bp);

    if (b->getState() != State::None) setupDefault(); // board hasn't been set up already 

    /* TO-DO Alan: Set game state to active */
    while (b->getState() == State::InPlay) {
        while (!b->move(wp->getMove())) continue;
        if (b->getState() != State::InPlay) break;
        while (!b->move(bp->getMove())) continue; 
    }

    // always ends on loser's turn
    if (b->getState() == State::Draw || b->getState() == State::Stalemate) {
        whiteScore += 0.5;
        blackScore += 0.5; 
    }
    else if (b->getTurn() == Side::W) blackScore++;
    else whiteScore++;
}

Game::~Game() {
    delete wp; 
    delete bp; 
}
