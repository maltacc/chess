#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "move.h"
class Player {
    Side side;
    public: 
        Player(Side side);
        virtual Move getMove() = 0;
        virtual ~Player(); 
}; 

#endif 
