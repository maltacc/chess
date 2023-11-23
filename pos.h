#ifndef __POS_H__
#define __POS_H__
#include <string>
#include <compare>

class Pos {
    int rank, file; 
    auto operator<=>(const Pos &other) const = default;

    public: 
        Pos(); 
        Pos(string p); // takes in position as a string 
        Pos(int x, int y); // overloaded constructor with param coordinates 0-7
        int getRank(); 
        int getFile();
        bool operator!=(const Pos &other);
        ~Pos(); 
}; 

#endif 