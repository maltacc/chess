#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer: public Player {
    Board *board;

    public: 
        Computer(Side side, Board *board); 
        virtual Move getMove() = 0; 
        virtual ~Computer();
}; 

#endif 
