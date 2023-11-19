#ifndef __BOARD_H__
#define __BOARD_H__
#include "square.h"
#include "pos.h"
#include "piece.h" // high coupling

class Board {
    Square b[8][8];  

    public: 
        Board(); 
        void clear(); // clears board for new game
        void place(Type p, Pos pos); 
        void remove(Pos &p); 
        void move(Pos start, Pos end);
        ~Board(); 
}; 

#endif 