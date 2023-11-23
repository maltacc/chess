#include "PMove.h"

PMove::PMove(Pos start, Pos end, char promotion): Move(start, end), promotion{promotion} {}

char PMove::getPromo(){
    return promotion;
}
