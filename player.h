#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "legalboard.h"

class Player {
    protected: 
        LegalBoard *b; 

    public: 
        Player();
        virtual Move getMove() = 0;
        virtual ~Player(); 
}; 

#endif 
