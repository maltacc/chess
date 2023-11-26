#include "l3.h"
using namespace std; 

L3::L3(LegalBoard *board): Computer{board} {}

Move L3::getMove() {
    // avoid getting captured by checking if square is attacked 
    // capturing moves 
    // checks
}

L3::~L3() {}
