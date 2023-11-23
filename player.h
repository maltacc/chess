#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "legalboard.h"
#include "PMove.h"

class Player {
    protected: 
        LegalBoard *b; 

    public: 
        Player();
        virtual PMove getMove() = 0;
        virtual ~Player(); 
}; 

#endif 
