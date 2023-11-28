#ifndef __BOARD_H__
#define __BOARD_H__
#include "square.h"
#include "observer.h"
#include <vector>
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
        // The following 4 of the Big 5 will be used exclusively for copying/assigning 
        // temporary boards for the Players. Since we don't wan't to notify observers, 
        // we don't copy this field over
        Board(const Board &other); // copy ctor
        Board(Board &&other); // move ctor
        Board &operator=(const Board &other); // copy assignment operator
        Board &operator=(Board &&other); // move assignment operator

        void clear(); // clears board for new game
        void place(Piece piece, Pos pos);
        void remove(Pos p);
        State getState();
        Side getTurn();
        const Piece* getPiece(int i, int j); 
        void setTurn(Side s);
        virtual bool move(Move m);
        void attach(Observer* o); // observer pattern
        void notifyObservers(vector<Pos> v); // v contains new positions
        virtual ~Board() noexcept;
}; 

#endif
