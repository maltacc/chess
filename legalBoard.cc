#include "legalBoard.h"
using namespace std;

void LegalBoard::updateLegalMoves() {
    legalMoves.clear(); 
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            
        }
    }
}

void LegalBoard::generateAttackMap() {
    Side attackingSide = turn == Side::W ? Side::B : Side::W; 

    // reset attack map
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) b[i][j].setAttacked(0); 
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (b[i][j].isEmpty() || (*b[i][j]).getSide() == turn) continue;

            char p = getPiece(i, j);  
            // square contains a knight, pawn, or king (leaping pieces) 
            // Knight:
            if (p == 'n' || p == 'N') {
                if (inBounds(i+2, j+1)) b[i+2][j+1].setAttacked(1); 
                if (inBounds(i-2, j+1)) b[i-2][j+1].setAttacked(1); 
                if (inBounds(i+2, j-1)) b[i+2][j-1].setAttacked(1); 
                if (inBounds(i-2, j-1)) b[i-2][j-1].setAttacked(1); 
                if (inBounds(i+1, j+2)) b[i+1][j+2].setAttacked(1); 
                if (inBounds(i-1, j+2)) b[i-1][j+2].setAttacked(1); 
                if (inBounds(i+1, j-2)) b[i+1][j-2].setAttacked(1); 
                if (inBounds(i-1, j-2)) b[i-1][j-2].setAttacked(1); 
            }
            
            // Pawn:
            if (p == 'p' || p == 'P') {
                if ((*b[i][j]).getSide() == Side::B) {
                    if (inBounds(i+1, j-1)) b[i+1][j-1].setAttacked(1); 
                    if (inBounds(i+1, j+1)) b[i+1][j+1].setAttacked(1); 
                }
                else {
                    if (inBounds(i-1, j-1)) b[i-1][j-1].setAttacked(1); 
                    if (inBounds(i-1, j+1)) b[i-1][j+1].setAttacked(1); 
                }
            }

            // King:
            if (p == 'k' || p == 'K') {
                if (inBounds(i+1, j+1)) b[i+1][j+1].setAttacked(1); 
                if (inBounds(i+1, j)) b[i+1][j].setAttacked(1); 
                if (inBounds(i+1, j-1)) b[i+1][j-1].setAttacked(1); 
                if (inBounds(i, j+1)) b[i][j+1].setAttacked(1); 
                if (inBounds(i, j-1)) b[i][j-1].setAttacked(1); 
                if (inBounds(i-1, j+1)) b[i-1][j+1].setAttacked(1); 
                if (inBounds(i-1, j)) b[i-1][j].setAttacked(1); 
                if (inBounds(i-1, j-1)) b[i-1][j-1].setAttacked(1); 
            }

            // Diagonal Moves (Bishop or Queen):
            if (p == 'b' || p == 'B' || p == 'q' || p == 'Q') {
                for (int r = i - 1, c = j + 1; r >= 0 && c <= 7; r--, c++) {
                    b[r][c].setAttacked(1); 
                    if (!b[r][c].isEmpty() && !getPiece(r, c) == (turn == Side::W ? 'K' : 'k')) break;
                }
                for (int r = i + 1, c = j + 1; r <= 7 && c <= 7; r++, c++) {
                    b[r][c].setAttacked(1); 
                    if (!b[r][c].isEmpty() && !getPiece(r, c) == (turn == Side::W ? 'K' : 'k')) break;
                }
                for (int r = i - 1, c = j - 1; r >= 0 && c >= 0; r--, c--) {
                    b[r][c].setAttacked(1); 
                    if (!b[r][c].isEmpty() && !getPiece(r, c) == (turn == Side::W ? 'K' : 'k')) break;
                }
                for (int r = i + 1, c = j - 1; r <= 7 && c >= 0; r++, c--) {
                    b[r][c].setAttacked(1); 
                    if (!b[r][c].isEmpty() && !getPiece(r, c) == (turn == Side::W ? 'K' : 'k')) break;
                }
            }

            // Perpendicular Moves (Rook or Queen):
            if (p == 'r' || p == 'R' || p == 'q' || p == 'Q') {
                for (int r = i + 1; r < 8; r++){
                    b[r][j].setAttacked(1); 
                    if (!b[r][j].isEmpty() && !getPiece(r, j) == (turn == Side::W ? 'K' : 'k')) break;
                }
                for (int r = i - 1; r >= 0; r--){
                    b[r][j].setAttacked(1); 
                    if (!b[r][j].isEmpty() && !getPiece(r, j) == (turn == Side::W ? 'K' : 'k')) break;
                }
                for (int c = j + 1; c < 8; c++){
                    b[i][c].setAttacked(1); 
                    if (!b[i][c].isEmpty() && !getPiece(i, c) == (turn == Side::W ? 'K' : 'k')) break;
                }
                for (int c = j - 1; c >= 0; c--){
                    b[i][c].setAttacked(1); 
                    if (!b[i][c].isEmpty() && !getPiece(i, c) == (turn == Side::W ? 'K' : 'k')) break;
                }
            }
        }
    }
}

void LegalBoard::updateKingMoves(Pos p) {

}

void LegalBoard::updateQueenMoves(Pos p) {
    int r = p.getRank(), c = p.getFile(); 

        // loop through diagonals and add to legalMoves

        // move towards upper right corner of board
        for (int i = r, j = c; i >= 0 && j <= 7; i--, j++) { 
            // if the path is blocked by a king, the path is illegal
            if (getPiece(i, j) == 'K' || getPiece(i, j) == 'k') continue; 
            if ((*b[i][j]).getSide() != turn) legalMoves.push_back(Move{p, Pos{i, j}});  
        }

        // move towards upper left corner of board
        for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) { 
            // if the path is blocked by a king, the path is illegal
            if (getPiece(i, j) == 'K' || getPiece(i, j) == 'k') continue; 
            if ((*b[i][j]).getSide() != turn) legalMoves.push_back(Move{p, Pos{i, j}});  
        }

        // move towards lower right corner of board
        for (int i = r, j = c; i <= 7 && j <= 7; i++, j++) { 
            // if the path is blocked by a king, the path is illegal
            if (getPiece(i, j) == 'K' || getPiece(i, j) == 'k') continue; 
            if ((*b[i][j]).getSide() != turn) legalMoves.push_back(Move{p, Pos{i, j}});  
        }

        // move towards lower left corner of board
        for (int i = r, j = c; i <= 7 && j >= 0; i++, j--) { 
            // if the path is blocked by a king, the path is illegal
            if (getPiece(i, j) == 'K' || getPiece(i, j) == 'k') continue; 
            if ((*b[i][j]).getSide() != turn) legalMoves.push_back(Move{p, Pos{i, j}});  
        }
}

void LegalBoard::updateRookMoves(Pos p) {

}
void LegalBoard::updateBishopMoves(Pos p) {}
void LegalBoard::updateKnightMoves(Pos p) {}
void LegalBoard::updatePawnMoves(Pos p) {}
bool LegalBoard::insufficientMaterial() {
    int knightCount = 0;
    int bishopCount = 0;
    bool majorPieceOrPawn = false;
}
void LegalBoard::updateState() {}
Side LegalBoard::getTurn() {}

bool LegalBoard::move(Move m) {
    bool proceed = 0; 
    for (auto move: legalMoves) {
        if (!(move.getStart() != m.getStart()) && !(move.getEnd() != m.getEnd())) proceed = 1;
    }
    if (!proceed) return 0; // move is not in list of legal moves

    int xi = m.getStart().getRank(), yi = m.getStart().getFile(), 
        xf = m.getEnd().getRank(), yf = m.getEnd().getFile(); 

    b[xi][yi].move(b[xf][yf]); 
    notifyObservers(); 
    return 1; // move was successful
}

void LegalBoard::promote(char piece) {
    if (piece >= 'a' & piece <= 'z') { // black piece
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (getPiece(i, j) == 'p' || getPiece(i, j) == 'P') {
                    b[i][j].addPiece(piece); 
                }
            }
        }
    }
}
auto LegalBoard::begin(){ return legalMoves.begin(); }
auto LegalBoard::end(){ return legalMoves.end(); }
