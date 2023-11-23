#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"

class Computer: public Player {
    Board *board;

    public: 
        Computer(Board *board);
        virtual ~Computer();
}; 

#endif 
