#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"
#include "move.h"

class Computer: public Player {
    int lvl; // difficulty level

    public: 
        Computer(int lvl); 
        virtual Move getMove(); 
        virtual ~Computer();
}; 

#endif 
