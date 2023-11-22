#ifndef __L1_H__
#define __L1_H__
#include "computer.h"

class L1: public Computer {
    public: 
        L1(Board *board);
        Move getMove() override; 
        ~L1();
};

#endif
