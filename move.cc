#include "move.h"
using namespace std; 

Move::Move(Pos start, Pos end): start{start}, end{end} {}

Pos Move::getStart() { return start; }

Pos Move::getEnd() { return end; }
