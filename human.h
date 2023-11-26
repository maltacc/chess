#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"

class Human: public Player {
    public:
        Human(); 
        Move getMove();     
        ~Human(); 
}; 

#endif 
