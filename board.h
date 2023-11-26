#ifndef __BOARD_H__
#define __BOARD_H__
#include "square.h"
#include "observer.h"
#include <iostream>
using namespace std;

enum class State{Checkmate, Stalemate, Draw, Resign, InPlay, None};

class Board {
    protected:
        Square b[8][8];
        vector<Observer*> observers;
        State state;
        Side turn; 

    public: 
        Board(); 
        Board(const Board &other); // copy ctor
        void clear(); // clears board for new game
        void place(Piece piece, Pos pos);
        void remove(Pos p);
        State getState();
        Side getTurn();
        const Piece* getPiece(int i, int j); 
        void setTurn(Side s);
        virtual bool move(Move m);
        void attach(Observer* o); // observer pattern
        void notifyObservers(); 
        virtual ~Board() noexcept;
}; 

#endif
