#ifndef __L3_H__
#define __L3_H__
#include "computer.h"

class L3: public Computer {
    public: 
        L3(Side side, Board *board);
        Move getMove() override; 
        ~L3();
};

#endif
