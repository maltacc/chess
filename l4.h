#ifndef __L4_H__
#define __L4_H__
#include "computer.h"

class L4: public Computer {
    public: 
        L4(LegalBoard *b);
        Move getMove() override; 
        ~L4();
};

#endif
