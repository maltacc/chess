#ifndef __OBSERVER_H__
#define __OBSERVER_H__
#include "board.h"

class Observer {
    public: 
        virtual void notify(vector<Pos> v, Board &b) = 0; 
        virtual ~Observer() = default;
}; 

#endif 
