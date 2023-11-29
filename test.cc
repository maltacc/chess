#include <iostream> 
#include "game.h"
using namespace std; 

int main() {
    // test legal board
    LegalBoard b; 
    Game g{&b}; 
    g.run("human", "human");
}
