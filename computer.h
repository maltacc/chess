#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include "player.h"
#include <time.h>
#include <stdlib.h>

class Computer: public Player {
    LegalBoard lb;

    public: 
        Computer(LegalBoard *board);
        virtual ~Computer();
}; 

#endif 
