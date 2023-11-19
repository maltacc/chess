#ifndef __POS_H__
#define __POS_H__
#include <string>

class Pos {
    int rank, file; 

    public: 
        Pos(string p); // takes in position as a string 
        string toString(); 
        int getRank(); 
        int getFile();
}; 

#endif 