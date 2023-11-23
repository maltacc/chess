#ifndef __PMOVE_H__
#define __PMOVE_H__
#include "move.h"

class PMove: public Move {
    char promotion;
    public:
        PMove(Pos start, Pos end, char promotion);
        char getPromo();
};


#endif
