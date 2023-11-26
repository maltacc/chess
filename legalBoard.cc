#include "legalBoard.h"
using namespace std;

bool LegalBoard::sameType(int rank_index, int file_index, Type t) {
    return b[rank_index][file_index].piece()->getType() == t;
}

bool LegalBoard::sameSide(int rank_index, int file_index, Side s) {
    return b[rank_index][file_index].piece()->getSide() == s;
}

bool LegalBoard::inBounds(int x, int y) {
    return (x >= 0) && (x < 8) && (y >= 0) && (y < 8); 
}

void LegalBoard::addDiagonals(int r, int c) {
        // move towards upper right corner of board
        for (int i = r, j = c; i >= 0 && j <= 7; i--, j++) { 
            if (b[i][j].isEmpty()) legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}}); 
            else {
                if (!sameSide(i, j, turn))
                    legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});  // enemy piece, can capture
                break;  // can only capture or move until the first enemy piece it encounters
            }
        }

        // move towards upper left corner of board
        for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) { 
            if (b[i][j].isEmpty()) legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}}); 
            else {
                if (!sameSide(i, j, turn))
                    legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});  // enemy piece, can capture
                break;  // can only capture or move until the first enemy piece it encounters
            }
        }

        // move towards lower right corner of board
        for (int i = r, j = c; i <= 7 && j <= 7; i++, j++) { 
            if (b[i][j].isEmpty()) legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}}); 
            else {
                if (!sameSide(i, j, turn))
                    legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});  // enemy piece, can capture
                break;  // can only capture or move until the first enemy piece it encounters
            }
        }

        // move towards lower left corner of board
        for (int i = r, j = c; i <= 7 && j >= 0; i++, j--) { 
            if (b[i][j].isEmpty()) legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}}); 
            else {
                if (!sameSide(i, j, turn))
                    legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});  // enemy piece, can capture
                break;  // can only capture or move until the first piece it encounters
            }
        }
}

void LegalBoard::addPerpendiculars(int r, int c) {
    // check vertical path above piece
    for (int i = r - 1; i >= 0; i--) {
        if (b[i][c].isEmpty()) legalMoves.push_back(Move{Pos{r, c}, Pos{i, c}}); 
        else {
            if (!sameSide(i, c, turn)) 
                legalMoves.push_back(Move{Pos{r, c}, Pos{i, c}});  // enemy piece, can capture
            break;  // can only capture or move until the first piece it encounters
        }
    }

    // check vertical path below piece 
    for (int i = r + 1; i < 8; i++) {
        if (b[i][c].isEmpty()) legalMoves.push_back(Move{Pos{r, c}, Pos{i, c}}); 
        else {
            if (!sameSide(i, c, turn)) 
                legalMoves.push_back(Move{Pos{r, c}, Pos{i, c}});  // enemy piece, can capture
            break;  // can only capture or move until the first enemy piece it encounters
        }
    }

    // check horizontal path to the left of piece
    for (int i = c; i >= 0; i--) {
        if (b[r][i].isEmpty()) legalMoves.push_back(Move{Pos{r, c}, Pos{r, i}}); 
        else {
            if (!sameSide(r, i, turn)) 
                legalMoves.push_back(Move{Pos{r, c}, Pos{r, i}});  // enemy piece, can capture
            break;  // can only capture or move until the first enemy piece it encounters
        }
    }

    // check horizontal path to the right of piece
    for (int i = c; i < 8; i++) {
        if (b[r][i].isEmpty()) legalMoves.push_back(Move{Pos{r, c}, Pos{r, i}}); 
        else {
            if (!sameSide(r, i, turn)) 
                legalMoves.push_back(Move{Pos{r, c}, Pos{r, i}});  // enemy piece, can capture
            break;  // can only capture or move until the first enemy piece it encounters
        }
    }
}

void LegalBoard::generateAttackMap() {
    Side attackingSide = (turn == Side::W ? Side::B : Side::W); 

    // reset attack map
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) b[i][j].setAttacked(0); 
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (b[i][j].isEmpty() || getPiece(i, j)->getSide() == turn) continue;

            Type p = getPiece(i, j)->getType();  

            // square contains a knight, pawn, or king (leaping pieces) 
            // Knight:
            if (p == Type::N) {
                if (inBounds(i+2, j+1)) b[i+2][j+1].addAttacked(); 
                if (inBounds(i-2, j+1)) b[i-2][j+1].addAttacked(); 
                if (inBounds(i+2, j-1)) b[i+2][j-1].addAttacked(); 
                if (inBounds(i-2, j-1)) b[i-2][j-1].addAttacked(); 
                if (inBounds(i+1, j+2)) b[i+1][j+2].addAttacked(); 
                if (inBounds(i-1, j+2)) b[i-1][j+2].addAttacked(); 
                if (inBounds(i+1, j-2)) b[i+1][j-2].addAttacked(); 
                if (inBounds(i-1, j-2)) b[i-1][j-2].addAttacked(); 
            }
            
            // Pawn:
            if (p == Type::P) {
                if (getPiece(i, j)->getSide() == Side::B) {
                    if (inBounds(i+1, j-1)) b[i+1][j-1].addAttacked();
                    if (inBounds(i+1, j+1)) b[i+1][j+1].addAttacked(); 
                }
                else {
                    if (inBounds(i-1, j-1)) b[i-1][j-1].addAttacked(); 
                    if (inBounds(i-1, j+1)) b[i-1][j+1].addAttacked(); 
                }
            }

            // King:
            if (p == Type::K) {
                if (inBounds(i+1, j+1)) b[i+1][j+1].addAttacked();
                if (inBounds(i+1, j)) b[i+1][j].addAttacked();
                if (inBounds(i+1, j-1)) b[i+1][j-1].addAttacked(); 
                if (inBounds(i, j+1)) b[i][j+1].addAttacked();
                if (inBounds(i, j-1)) b[i][j-1].addAttacked(); 
                if (inBounds(i-1, j+1)) b[i-1][j+1].addAttacked(); 
                if (inBounds(i-1, j)) b[i-1][j].addAttacked();
                if (inBounds(i-1, j-1)) b[i-1][j-1].addAttacked(); 
            }

            // Diagonal Moves (Bishop or Queen):
            if (p == Type::B || p == Type::Q) {
                for (int r = i - 1, c = j + 1; r >= 0 && c <= 7; r--, c++) {
                    b[r][c].addAttacked();
                    // We do not care about which Side the piece is on because we need to account
                    // for pieces that are defended by ally pieces.
                    if (!b[r][c].isEmpty() && !(*getPiece(r, c) == Piece(Type::K, turn))) break;
                }
                for (int r = i + 1, c = j + 1; r <= 7 && c <= 7; r++, c++) {
                    b[r][c].addAttacked(); 
                    if (!b[r][c].isEmpty() && !(*getPiece(r, c) == Piece(Type::K, turn))) break;
                }
                for (int r = i - 1, c = j - 1; r >= 0 && c >= 0; r--, c--) {
                    b[r][c].addAttacked(); 
                    if (!b[r][c].isEmpty() && !(*getPiece(r, c) == Piece(Type::K, turn))) break;
                }
                for (int r = i + 1, c = j - 1; r <= 7 && c >= 0; r++, c--) {
                    b[r][c].addAttacked(); 
                    if (!b[r][c].isEmpty() && !(*getPiece(r, c) == Piece(Type::K, turn))) break;
                }
            }

            // Manhattan Moves (Rook or Queen):
            if (p == Type::R || p == Type::Q) {
                for (int r = i + 1; r < 8; r++){
                    b[r][j].addAttacked();
                    if (!b[r][j].isEmpty() && !(*getPiece(r, j) == Piece(Type::K, turn))) break;
                }
                for (int r = i - 1; r >= 0; r--){
                    b[r][j].addAttacked(); 
                    if (!b[r][j].isEmpty() && !(*getPiece(r, j) == Piece(Type::K, turn))) break;
                }
                for (int c = j + 1; c < 8; c++){
                    b[i][c].addAttacked(); 
                    if (!b[i][c].isEmpty() && !(*getPiece(i, c) == Piece(Type::K, turn))) break;
                }
                for (int c = j - 1; c >= 0; c--){
                    b[i][c].addAttacked(); 
                    if (!b[i][c].isEmpty() && !(*getPiece(i, c) == Piece(Type::K, turn))) break;
                }
            }
        }
    }
}

bool LegalBoard::canKingBeHere(int rank_index, int file_index){
    return inBounds(rank_index, file_index) && !b[rank_index][file_index].isAttacked() && 
        (b[rank_index][file_index].isEmpty() || !sameSide(rank_index, file_index, turn));
}

int LegalBoard::kingAttackerCount(){
    Pos kingPos = (turn == Side::W ? whiteKing : blackKing);
    return b[kingPos.getRank()][kingPos.getFile()].attackCount();
}

void LegalBoard::updateKingMoves(Pos p) {
    int r = p.getRank(), c = p.getFile(); 

    // 3 squares above King
    if (r - 1 >= 0) {
        for (int i = c - 1; i <= c + 1; i++) {
            if (canKingBeHere(r - 1, i)) legalMoves.push_back(Move{p, Pos{r - 1, i}}); 
        }
    }

    // 2 squares on each side of King
    if (canKingBeHere(r, c - 1)) legalMoves.push_back(Move{p, Pos{r, c - 1}}); 
    if (canKingBeHere(r, c + 1)) legalMoves.push_back(Move{p, Pos{r, c + 1}}); 

    // 3 squares below King 
    if (r + 1 >= 0 && r + 1 < 8) {
        for (int i = c - 1; i <= c + 1; i++) {
            if (canKingBeHere(r + 1, i)) legalMoves.push_back(Move{p, Pos{r + 1, i}}); 
        }
    }
}

void LegalBoard::updateQueenMoves(Pos p, bool isPinned) {
    int r = p.getRank(), c = p.getFile(); 
    switch (kingAttackerCount()) {
    case 0:
        break;
    case 1:
        break;
    default:
        break;
    }
    // Is this piece pinned?
        // if so...
    // Otherwise:
    addDiagonals(r, c); 
    addPerpendiculars(r, c); 
}

void LegalBoard::updateRookMoves(Pos p, bool isPinned) {
    int r = p.getRank(), c = p.getFile(); 
    addPerpendiculars(r, c); 
}

void LegalBoard::updateBishopMoves(Pos p, bool isPinned) {
    int r = p.getRank(), c = p.getFile(); 
    addDiagonals(r, c); 
}

void LegalBoard::addKnightLeaps(int ri, int ci, int rf, int cf) {
    if (inBounds(rf, cf)) {
        if (b[rf][cf].isEmpty() || b[rf][cf].piece()->getSide() != turn) 
            legalMoves.push_back(Move{Pos{ri, ci}, Pos{rf, cf}});   
    }
}

void LegalBoard::updateKnightMoves(Pos p, bool isPinned) {
    if (isPinned) return; // There are no possible moves for the knight if its pinned
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

void LegalBoard::updatePawnMoves(Pos p, bool isPinned) {
    int r = p.getFile(), c = p.getFile();
    if (sameSide(r, c, Side::W)) {
        if (inBounds(r - 1, c) && b[r - 1][c].isEmpty()) legalMoves.push_back(Move{p, Pos{r - 1, c}}); 
        if (inBounds(r - 2, c) && b[r - 2][c].isEmpty() && (r == 6)) legalMoves.push_back(Move{p, Pos{r - 2, c}}); 
    }
    if (sameSide(r, c, Side::B)) {
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
            Type p = b[r][c].piece()->getType(); 
            if (p == Type::R || p == Type::Q || p == Type::P) return 0; 
            else if (p == Type::N) {
                knightCount++; 
                if (knightCount == 2) return 1; 
            }
            else if (p == Type::B) {
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

void LegalBoard::promote(Type type) {
    int rank_index = (turn == Side::W ? 0 : 7);
    for (int j = 0; j < 8; j++) {
        if (sameType(rank_index, j, Type::P)) {
            b[rank_index][j].addPiece(Piece(type, turn)); 
        }
    }
}
auto LegalBoard::legalMovesBegin(){ return legalMoves.begin(); }
auto LegalBoard::legalMovesEnd(){ return legalMoves.end(); }

bool LegalBoard::isPinned(int rank_index, int file_index){
    // NOTE TO SELF: DO THIS FUNCTION BEFORE THE updatePieceMoves FUNCTIONS!!!
    // - If this piece is the current turn's king, return false
    // - If this piece is not along the same diagonal / rank as the current turn's
    //   king, return false.
    // - If this piece is on the same diagonal:
    //    - If this piece is sandwiched between Bishop/Queen and our king, return true;
    //    - return false; otherwise
    // - If this piece is on the same file/rank: (this is the else statement)
    //    - If this piece is between rook/queen and our king return true;
    //    - return false;
    return false;
}

void LegalBoard::updateLegalMoves() {
    legalMoves.clear(); 
    generateAttackMap();
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!sameSide(i, j, turn)) continue;
            bool pin = isPinned(i, j);
            switch (b[i][j].piece()->getType()){
                case Type::P:
                    updatePawnMoves(Pos(i, j), pin);
                    break;
                case Type::B:
                    updateBishopMoves(Pos(i, j), pin);
                    break;
                case Type::R:
                    updateRookMoves(Pos(i, j), pin);
                    break;
                case Type::N:
                    updateKnightMoves(Pos(i, j), pin);
                    break;
                case Type::Q:
                    updateQueenMoves(Pos(i, j), pin);
                    break;
                default:
                    updateKingMoves(Pos(i, j));
            }
        }
    }
}
