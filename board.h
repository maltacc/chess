#ifndef __BOARD_H__
#define __BOARD_H__
#include "square.h"
#include "pos.h"
#include "move.h"
#include "observer.h"

class Board {
    Square b[8][8];  
    bool isValidMove(Move m); 
    vector<Observer*> observers;  

    public: 
        Board(); 
        void clear(); // clears board for new game
        void place(char piece, Pos pos, int turn); 
        void remove(Pos p); 
        void move(Move m);
        void attach(Observer* o); // observer pattern
        void notifyObservers(); 
        char getPiece(int r, int c); 
        ~Board(); 
}; 

#endif 