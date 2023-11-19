#ifndef __POS_H__
#define __POS_H__
#include <string>

class Pos {
    int rank, file; 

    public: 
        Pos(); 
        Pos(string p); // takes in position as a string 
        int getRank(); 
        int getFile();
}; 

#endif 