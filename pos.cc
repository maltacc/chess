#include "pos.h"
using namespace std; 

Pos::Pos(string p) {
    rank = p[1] - '0'; // cnovert char to int
    file = p[0] - 'a'; 
}

string Pos::toString() {
    string res = ""; 
    res = file + 'a' + rank + '0'; 
    return res; 
}

int Pos::getRank() { return rank; }

int Pos::getFile() { return file; }
