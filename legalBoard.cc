#include "legalBoard.h"
using namespace std;

void LegalBoard::updateLegalMoves() {}
void LegalBoard::updateKing(Pos p) {}
void LegalBoard::updateQueen(Pos p) {}
void LegalBoard::updateRook(Pos p) {}
void LegalBoard::updateBishop(Pos p) {}
void LegalBoard::updateKnight(Pos p) {}
void LegalBoard::updatePawn(Pos p) {}
bool LegalBoard::insufficientMaterial() {
    
}
void LegalBoard::updateState() {}
auto LegalBoard::begin(){ return legalMoves.begin(); }