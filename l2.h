#ifndef __L2_H__
#define __L2_H__
#include "computer.h"

class L2: public Computer {
    public: 
        L2(Board *board);
        PMove getMove() override; 
        ~L2();
};

#endif
