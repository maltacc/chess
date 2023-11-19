#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "move.h"
#include "computer.h"

class Level: public Computer {
    public: 
        virtual Move getMove() = 0; // factory method
}; 

#endif 
