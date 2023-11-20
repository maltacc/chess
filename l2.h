#ifndef __L2_H__
#define __L2_H__
#include "computer.h"

class L2: public Computer {
    public: 
        L2(Side side, Board *board);
        Move getMove() override; 
        ~L2();
};

#endif
