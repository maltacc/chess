#ifndef __L4_H__
#define __L4_H__
#include "level.h"

class L4: public Level {
    public: 
        Move getMove() override; 
};

#endif
