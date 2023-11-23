#include "legalBoard.h"
using namespace std;

void LegalBoard::updateLegalMoves() {
    legalMoves.clear(); 
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            
        }
    }
}

bool LegalBoard::inBounds(int x, int y) {
    return (x >= 0) && (x < 8) && (y >= 0) && (y < 8); 
}

void LegalBoard::addDiagonals(int r, int c) {
        // move towards upper right corner of board
        for (int i = r, j = c; i >= 0 && j <= 7; i--, j++) { 
            // if the path is blocked by a king, the path is illegal

            // *** TO-DO: if square is empty, getPiece has an error. check if empty. current soln is in getPiece
            if (getPiece(i, j) == 'K' || getPiece(i, j) == 'k') continue; // ignore the king
            if ((*b[i][j]).getSide() != turn) legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});  // enemy piece, can capture
            if (!b[i][j].isEmpty()) break; // queen can only capture or move until the first piece it encounters
        }

        // move towards upper left corner of board
        for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) { 
            // if the path is blocked by a king, the path is illegal
            if (getPiece(i, j) == 'K' || getPiece(i, j) == 'k') continue; 
            if ((*b[i][j]).getSide() != turn) legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}}); 
            if (!b[i][j].isEmpty()) break; // queen can only capture or move until the first piece it encounters
        }

        // move towards lower right corner of board
        for (int i = r, j = c; i <= 7 && j <= 7; i++, j++) { 
            // if the path is blocked by a king, the path is illegal
            if (getPiece(i, j) == 'K' || getPiece(i, j) == 'k') continue; 
            if ((*b[i][j]).getSide() != turn) legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});  
            if (!b[i][j].isEmpty()) break; // queen can only capture or move until the first piece it encounters
        }

        // move towards lower left corner of board
        for (int i = r, j = c; i <= 7 && j >= 0; i++, j--) { 
            // if the path is blocked by a king, the path is illegal
            if (getPiece(i, j) == 'K' || getPiece(i, j) == 'k') continue; 
            if ((*b[i][j]).getSide() != turn) legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});  
            if (!b[i][j].isEmpty()) break; // queen can only capture or move until the first piece it encounters
        }
}

void LegalBoard::addPerpendiculars(int r, int c) {
    // check vertical path above piece
    for (int i = r - 1; i >= 0; i--) {
        if (getPiece(i, c) == 'K' || getPiece(i, c) == 'k') continue; 
        if ((*b[i][c]).getSide() != turn) legalMoves.push_back(Move{Pos{r, c}, Pos{i, c}}); // if enemy piece, we can move
        if (!b[i][c].isEmpty()) break; // we can only move up to that occupied piece
    }

    // check vertical path below piece 
    for (int i = r + 1; i < 8; i++) {
        if (getPiece(i, c) == 'K' || getPiece(i, c) == 'k') continue; 
        if ((*b[i][c]).getSide() != turn) legalMoves.push_back(Move{Pos{r, c}, Pos{i, c}}); // if enemy piece, we can move
        if (!b[i][c].isEmpty()) break; // we can only move up to that occupied piece
    }

    // check horizontal path to the left of piece
    for (int i = c; i >= 0; i--) {
        if (getPiece(i, c) == 'K' || getPiece(i, c) == 'k') continue; 
        if ((*b[i][c]).getSide() != turn) legalMoves.push_back(Move{Pos{r, c}, Pos{i, c}}); // if enemy piece, we can move
        if (!b[i][c].isEmpty()) break; // we can only move up to that occupied piece
    }

    // check horizontal path to the right of piece
    for (int i = c; i < 8; i++) {
        if (getPiece(i, c) == 'K' || getPiece(i, c) == 'k') continue; 
        if ((*b[i][c]).getSide() != turn) legalMoves.push_back(Move{Pos{r, c}, Pos{i, c}}); // if enemy piece, we can move
        if (!b[i][c].isEmpty()) break; // we can only move up to that occupied piece
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
    generateAttackMap(); 
    int r = p.getRank(), c = p.getFile(); 

    // 3 squares above King
    if (r - 1 >= 0 && r - 1 < 8) {
        for (int i = c - 1; i <= c + 1; i++) {
            if (!b[r - 1][i].isAttacked()) legalMoves.push_back(Move{p, Pos{r - 1, c}}); 
        }
    }

    // 2 squares on each side of King
    if (!b[r][c - 1].isAttacked()) legalMoves.push_back(Move{p, Pos{r, c - 1}}); 
    if (!b[r][c + 1].isAttacked()) legalMoves.push_back(Move{p, Pos{r, c + 1}}); 

    // 3 squares below King 
    if (r + 1 >= 0 && r + 1 < 8) {
        for (int i = c - 1; i <= c + 1; i++) {
            if (!b[r + 1][i].isAttacked()) legalMoves.push_back(Move{p, Pos{r + 1, c}}); 
        }
    }
}

void LegalBoard::updateQueenMoves(Pos p) {
    int r = p.getRank(), c = p.getFile(); 
    addDiagonals(r, c); 
    addPerpendiculars(r, c); 
}

void LegalBoard::updateRookMoves(Pos p) {
    int r = p.getRank(), c = p.getFile(); 
    addPerpendiculars(r, c); 
}

void LegalBoard::updateBishopMoves(Pos p) {
    int r = p.getRank(), c = p.getFile(); 
    addDiagonals(r, c); 
}

void LegalBoard::addKnightLeaps(int ri, int ci, int rf, int cf) {
    if (inBounds(rf, cf)) {
        if (b[rf][cf].isEmpty() || (*b[rf][cf]).getSide() != turn) 
            legalMoves.push_back(Move{Pos{ri, ci}, Pos{rf, cf}});   
    }
}

void LegalBoard::updateKnightMoves(Pos p) {
    int r = p.getRank(), c = p.getFile();
    addKnightLeaps(r, c, r - 1, c + 2); 
    addKnightLeaps(r, c, r + 1, c + 2); 
    addKnightLeaps(r, c, r - 1, c - 2); 
    addKnightLeaps(r, c, r + 1, c - 2); 
    addKnightLeaps(r, c, r + 2, c + 1); 
    addKnightLeaps(r, c, r + 2, c - 1); 
    addKnightLeaps(r, c, r - 2, c + 1); 
    addKnightLeaps(r, c, r - 2, c - 1); 
}

void LegalBoard::updatePawnMoves(Pos p) {
    int r = p.getFile(), c = p.getFile();
    if ((*b[r][c]).getSide() == Side::W) {
        if (inBounds(r - 1, c) && b[r - 1][c].isEmpty()) legalMoves.push_back(Move{p, Pos{r - 1, c}}); 
        if (inBounds(r - 2, c) && b[r - 2][c].isEmpty() && (r == 6)) legalMoves.push_back(Move{p, Pos{r - 2, c}}); 
    }
    if ((*b[r][c]).getSide() == Side::B) {
        if (inBounds(r + 1, c) && b[r + 1][c].isEmpty()) legalMoves.push_back(Move{p, Pos{r - 1, c}}); 
        if (inBounds(r + 2, c) && b[r + 2][c].isEmpty() && (r == 1)) legalMoves.push_back(Move{p, Pos{r - 2, c}}); 
    }
    // Q: do we consider en passant here? 
}

bool LegalBoard::insufficientMaterial() {
    int knightCount = 0; // need 2 knights 
    bool whiteSquareBishopCount = 0;
    bool blackSquareBishopCount = 0;
    bool majorPieceOrPawn = false; // if you find a rook or queen or pawn, the game can be won
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            char p = toupper(getPiece(r, c));
            if (p == 'R' || p == 'Q' || p == 'P') return 0; 
            else if (p == 'N') {
                knightCount++; 
                if (knightCount == 2) return 1; 
            }
            else if (p == 'B') {
                if ((r + c) % 2 == 0) whiteSquareBishopCount = 1; 
                else blackSquareBishopCount = 1; 
                if (whiteSquareBishopCount && blackSquareBishopCount) return 1; 
            }
        }
    }
    return 0; 
}

void LegalBoard::updateState() {}
Side LegalBoard::getTurn() { return turn; }

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
