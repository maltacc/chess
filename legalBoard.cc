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
    int knightCount = 0;
    int bishopCount = 0;
    bool majorPieceOrPawn = false;
}
void LegalBoard::updateState() {}
auto LegalBoard::begin(){ return legalMoves.begin(); }
auto LegalBoard::end(){ return legalMoves.end(); }
