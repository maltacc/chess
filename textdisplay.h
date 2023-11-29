#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "observer.h"
#include <iostream> 
#include "piece.h"
using namespace std;

class TextDisplay: public Observer {
    char td[8][8]; 
    char convertToChar(Piece p); 

    public: 
        TextDisplay(); 
        void notify(vector<Pos> v, Board &b) override; 
        ~TextDisplay(); 
        friend ostream &operator<<(ostream &out, const TextDisplay &td);
}; 

#endif 
