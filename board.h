#ifndef __BOARD_H__
#define __BOARD_H__
#include "square.h"
#include "pos.h"
#include "move.h"
#include "observer.h"

enum class State{Checkmate, Stalemate, Draw, Active, None};

class Board {
    protected:
        Square b[8][8];
        vector<Observer*> observers;
        State state = State::None;

    public: 
        friend class Player;
        Board(); 
        void clear(); // clears board for new game
        void place(char piece, Pos pos, Side turn); 
        void remove(Pos p); 
        State getState();
        virtual bool move(Move m);
        void attach(Observer* o); // observer pattern
        void notifyObservers(); 
        char getPiece(int r, int c);
        ~Board(); 
}; 

#endif
