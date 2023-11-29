#include "legalBoard.h"
#include <cstdlib>
using namespace std;

const int PERPDIR[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
const int DIAGDIR[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
const int NMOVES[DIM][2] = {
    {-1, 2}, {1, 2}, {-1, -2}, {1, -2}, 
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}
};
const Pos NO_EN_PASSANT = Pos{-1, -1};

LegalBoard::LegalBoard() {} 

LegalBoard::LegalBoard(const Board& other): Board{other} {}

bool LegalBoard::sameType(int rankIndex, int fileIndex, Type t) {
    return !(b[rankIndex][fileIndex].isEmpty()) && b[rankIndex][fileIndex].getPiece()->getType() == t;
}

bool LegalBoard::sameSide(int rankIndex, int fileIndex, Side s) {
    return !(b[rankIndex][fileIndex].isEmpty()) && b[rankIndex][fileIndex].getPiece()->getSide() == s;
}

bool LegalBoard::inBounds(int x, int y) {
    return (x >= 0) && (x < DIM) && (y >= 0) && (y < DIM); 
}

bool LegalBoard::addValidMoves(int r, int c, int i, int j) {
    if (b[i][j].isEmpty()) {
        legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});
    } else {
        if (!sameSide(i, j, turn)) {
            legalMoves.push_back(Move{Pos{r, c}, Pos{i, j}});  // enemy piece, can capture
        }
        else return 0;  // can only capture or move until the first enemy piece it encounters
    }
    return 1;
}

void LegalBoard::traverseDir(int r, int c, int rowDir, int colDir) {
    for (int i = r + rowDir, j = c + colDir; 
         i >= 0 && i < DIM && j >= 0 && j < DIM;
         i += rowDir, j += colDir)
        if (!addValidMoves(r, c, i, j)) break; 
}

void LegalBoard::addDiagonals(int r, int c) {
    const int DIR[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    for (int i = 0; i < 4; i++) traverseDir(r, c, DIAGDIR[i][0], DIAGDIR[i][1]); 
}

void LegalBoard::addPerpendiculars(int r, int c) {
    const int DIR[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; i++) traverseDir(r, c, PERPDIR[i][0], PERPDIR[i][1]); 
}

void LegalBoard::attackDir(int r, int c, int rowDir, int colDir) {
    for (int i = r + rowDir, j = c + colDir; 
         i >= 0 && i <= 7 && j >= 0 && j <= 7; 
         i += rowDir, j += colDir) {
        b[i][j].addAttacked();
        if (!b[r][c].isEmpty() && !(*getPiece(r, c) == Piece(Type::K, turn))) break;
    }
}

void LegalBoard::generateAttackMap() {
    Side attackingSide = (turn == Side::W ? Side::B : Side::W); 

    // reset attack map
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) b[i][j].setAttacked(0); 
    }

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (b[i][j].isEmpty() || getPiece(i, j)->getSide() == turn) continue;

            Type p = getPiece(i, j)->getType();  

            if (p == Type::N) { // Knight
                for (int k = 0; k < DIM; k++) {
                    int r = NMOVES[k][0] + i, c = NMOVES[k][1] + j; 
                    if (inBounds(r, c)) b[r][c].addAttacked(); 
                }
            }
            
            if (p == Type::P) { // Pawn
                if (getPiece(i, j)->getSide() == Side::B) {
                    if (inBounds(i+1, j-1)) b[i+1][j-1].addAttacked();
                    if (inBounds(i+1, j+1)) b[i+1][j+1].addAttacked(); 
                }
                else {
                    if (inBounds(i-1, j-1)) b[i-1][j-1].addAttacked(); 
                    if (inBounds(i-1, j+1)) b[i-1][j+1].addAttacked(); 
                }
            }

            if (p == Type::K) { // King
                const int KMOVES[DIM][2] = {
                    {1, 1}, {0, 1}, {1, 0}, {1, -1}, 
                    {-1, 1}, {-1, -1}, {0, -1}, {-1, 0}
                };
                for (int k = 0; k < DIM; k++) {
                    int r = KMOVES[k][0] + i, c = KMOVES[k][1] + j; 
                    if (inBounds(r, c)) b[r][c].addAttacked(); 
                }
            }

            // Diagonal Moves (Bishop or Queen):
            if (p == Type::B || p == Type::Q) {
                for (int i = 0; i < 4; i++) attackDir(i, j, DIAGDIR[i][0], DIAGDIR[i][1]); 
            }

            // Manhattan Moves (Rook or Queen):
            if (p == Type::R || p == Type::Q) {
                for (int i = 0; i < 4; i++) attackDir(i, j, DIAGDIR[i][0], DIAGDIR[i][1]); 
            }
        }
    }
}

bool LegalBoard::canKingBeHere(int rankIndex, int fileIndex) {
    return inBounds(rankIndex, fileIndex) && !b[rankIndex][fileIndex].isAttacked() && 
        (b[rankIndex][fileIndex].isEmpty() || !sameSide(rankIndex, fileIndex, turn));
}

void LegalBoard::updateKingInfo() {
    generateAttackMap();
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (sameType(i, j, Type::K)) {
                if (sameSide(i, j, turn)) kingAttackers = b[i][j].attackCount();
                if (sameSide(i, j, Side::W)) whiteKing = Pos{i, j};
                else blackKing = Pos{i, j};
            }
        }
    }
}

bool LegalBoard::isKingInCheck() {
    Pos kingPos = (turn == Side::W ? whiteKing : blackKing);
    int r = kingPos.getRank(), c = kingPos.getFile();
    for (auto incr : PERPDIR){
        for (int i = incr[0] + r, j = incr[1] + c; inBounds(i, j); i += incr[0], j += incr[1]){
            if (!b[i][j].isEmpty()) {
                if (!sameSide(i, j, turn) && (sameType(i, j, Type::Q) || sameType(i, j, Type::R))) return 1;
                break;
            }
        }
    }
    for (auto incr : DIAGDIR) {
        for (int i = incr[0] + r, j = incr[1] + c; inBounds(i, j); i += incr[0], j += incr[1]){
            if (!b[i][j].isEmpty()) {
                if (!sameSide(i, j, turn) && (sameType(i, j, Type::Q) || sameType(i, j, Type::B))) return 1;
                break;
            }
        }
    }
    for (auto incr : NMOVES) {
        int i = incr[0] + r, j = incr[1] + c;
        if (!b[i][j].isEmpty()) {
            if (!sameSide(i, j, turn) && sameType(i, j, Type::N)) return 1;
            break;
        }
    }

    if (turn == Side::W) {
        if (sameType(r + 1, c - 1, Type::P) && !sameSide(r + 1, c - 1, turn)) return 1;
        if (sameType(r + 1, c + 1, Type::P) && !sameSide(r + 1, c + 1, turn)) return 1;
    }
    else {
        if (sameType(r - 1, c - 1, Type::P) && !sameSide(r - 1, c - 1, turn)) return 1;
        if (sameType(r - 1, c + 1, Type::P) && !sameSide(r - 1, c + 1, turn)) return 1;
    }
    return 0;
}

bool LegalBoard::underCheck() { return kingAttackers; }

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
    if (r + 1 >= 0 && r + 1 < DIM) {
        for (int i = c - 1; i <= c + 1; i++) {
            if (canKingBeHere(r + 1, i)) legalMoves.push_back(Move{p, Pos{r + 1, i}}); 
        }
    }

    // check for castling!!!
    if (underCheck()) return;

    if (turn == Side::W) {
        if (castle.whiteKing && !(b[7][7].attackCount()) && 
            b[7][5].isEmpty() && b[7][6].isEmpty()) 
                legalMoves.push_back(Move{p, Pos{7, 6}});
        if (castle.whiteQueen && !(b[7][0].attackCount()) && 
            b[7][1].isEmpty() && b[7][2].isEmpty() && b[7][3].isEmpty())
                legalMoves.push_back(Move{p, Pos{7, 2}});
    } else {
        if (castle.blackKing && !(b[0][7].attackCount()) && 
            b[0][5].isEmpty() && b[0][6].isEmpty()) 
                legalMoves.push_back(Move{p, Pos{0, 6}});
        if (castle.whiteQueen && !(b[0][0].attackCount()) && 
            b[0][1].isEmpty() && b[0][2].isEmpty() && b[0][3].isEmpty())
                legalMoves.push_back(Move{p, Pos{0, 2}});
    }
}

void LegalBoard::updateQueenMoves(Pos p) {
    if (kingAttackers > 1) return;
    int r = p.getRank(), c = p.getFile(); 
    addDiagonals(r, c); 
    addPerpendiculars(r, c); 
}

void LegalBoard::updateRookMoves(Pos p) {
    if (kingAttackers > 1) return;
    int r = p.getRank(), c = p.getFile(); 
    addPerpendiculars(r, c); 
}

void LegalBoard::updateBishopMoves(Pos p) {
    if (kingAttackers > 1) return;
    int r = p.getRank(), c = p.getFile(); 
    addDiagonals(r, c); 
}

void LegalBoard::addKnightLeaps(int ri, int ci, int rf, int cf) {
    if (inBounds(rf, cf)) {
        if (b[rf][cf].isEmpty() || b[rf][cf].getPiece()->getSide() != turn) 
            legalMoves.push_back(Move{Pos{ri, ci}, Pos{rf, cf}});   
    }
}

void LegalBoard::updateKnightMoves(Pos p) {
    if (kingAttackers > 1) return; 
    int r = p.getRank(), c = p.getFile();
    for (int i = 0; i < DIM; i++) addKnightLeaps(r, c, NMOVES[i][0], NMOVES[i][1]); 
}

void LegalBoard::updatePawnMoves(Pos p) {
    if (kingAttackers > 1) return;
    int r = p.getFile(), c = p.getFile();
    if (sameSide(r, c, Side::W)) {
        if (inBounds(r - 1, c) && b[r - 1][c].isEmpty()) legalMoves.push_back(Move{p, Pos{r - 1, c}}); 
        if (inBounds(r - 2, c) && b[r - 2][c].isEmpty() && (r == 6)) legalMoves.push_back(Move{p, Pos{r - 2, c}}); 
    }
    if (sameSide(r, c, Side::B)) {
        if (inBounds(r + 1, c) && b[r + 1][c].isEmpty()) legalMoves.push_back(Move{p, Pos{r - 1, c}}); 
        if (inBounds(r + 2, c) && b[r + 2][c].isEmpty() && (r == 1)) legalMoves.push_back(Move{p, Pos{r - 2, c}}); 
    }
    
    if (epMove == NO_EN_PASSANT) return; // no en passant moves available
    
    // Adding possible en-passant moves.
    int epRank = epMove.getRank(), epFile = epMove.getFile();
    if (r == epRank && abs(epFile - c) == 1){
        if (turn == Side::B)
            legalMoves.push_back(Move{p, Pos{epRank + 1, epFile}}); 
        else 
            legalMoves.push_back(Move{p, Pos{epRank - 1, epFile}}); 
    }
}

bool LegalBoard::insufficientMaterial() {
    int knightCount = 0; // need 2 knights 
    bool whiteSquareBishopCount = 0;
    bool blackSquareBishopCount = 0;
    bool majorPieceOrPawn = false; // if you find a rook or queen or pawn, the game can be won
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            Type p = b[r][c].getPiece()->getType(); 
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

void LegalBoard::updateState() {
    // Checking stalemate / checkmate
    if (legalMoves.size() == 0) {
        if (underCheck()) {
            state = State::Checkmate;
        } else {
            state = State::Stalemate;
        }
        return;
    }
    if (insufficientMaterial()) state = State::Draw;
}

bool LegalBoard::isValidPosition() {
    Side temp = turn;
    turn = Side::W;
    updateKingInfo();
    if (underCheck()) return 0;
    turn = Side::B;
    updateKingInfo();
    if (underCheck()) return 0;
    turn = temp;
    int whiteKingCount = 0, blackKingCount = 0;
    for (int file = 0; file < DIM; file++) {
        if (sameType(0, file, Type::P) || sameType(DIM, file, Type::P)) return 0;
        for (int rank = 0; rank < DIM; rank++) {
            if (sameType(rank, file, Type::K)) {
                if ((sameSide(rank, file, Side::W) ? ++whiteKingCount : ++blackKingCount) > 1) return 0;
            }
        }
    }
    if (whiteKingCount != 1 || blackKingCount != 1) return 0;
    return 1;
}

void LegalBoard::activateGame() {
    if (!isValidPosition()) return;
    updateKingInfo();
    updateLegalMoves();
    updateState();
    if (state == State::None) state = State::InPlay;
}

Side LegalBoard::getTurn() { return turn; }

void LegalBoard::promote(Type type) {
    int rankIndex = (turn == Side::W ? 0 : 7);
    for (int j = 0; j < DIM; j++) {
        if (sameType(rankIndex, j, Type::P)) {
            b[rankIndex][j].addPiece(Piece(type, turn)); 
        }
    }
}

const vector<Move>& LegalBoard::getLegalMoves() { return legalMoves; }

// bool LegalBoard::isPinned(int rankIndex, int fileIndex) {
//     Pos kingPos = (turn == Side::W ? whiteKing : blackKing);
//     int rankDiff = kingPos.getRank() - rankIndex, fileDiff = kingPos.getFile() - rankIndex;
//     if (rankDiff == 0 && fileDiff == 0) return 0;
//     int rankDir = 0, fileDir = 0;
//     if (rankDiff != 0) rankDir = rankDiff / abs(rankDiff); 
//     if (fileDiff != 0) fileDir = fileDiff / abs(fileDiff); 
//     if (rankDiff == fileDiff || rankDiff == -fileDiff || rankDiff == 0 || fileDiff == 0) {
//         for (int i = rankIndex + rankDir, j = fileIndex + fileDir; 
//              i != rankIndex + rankDiff, j != fileIndex + fileDiff;
//              i += rankDir, j += fileDir)
//             if (!b[i][j].isEmpty()) return 0;
//         for (int i = rankIndex - rankDir, j = fileIndex - fileDir; inBounds(i, j); i -= rankDir, j -= fileDir) {
//             if (!b[i][j].isEmpty()) {
//                 if (rankDir == 0 || fileDir == 0) {
//                     if ((sameType(i, j, Type::R) || sameType(i, j, Type::Q)) && !sameSide(i, j, turn)) return 1;
//                 } else
//                     if ((sameType(i, j, Type::B) || sameType(i, j, Type::Q)) && !sameSide(i, j, turn)) return 1;
//                 return 0;
//             }
//         }
//     }
//     return 0;
// }

void LegalBoard::updateLegalMoves() {
    legalMoves.clear();
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (!sameSide(i, j, turn)) continue;
            switch (b[i][j].getPiece()->getType()) {
                case Type::P:
                    updatePawnMoves(Pos(i, j));
                    break;
                case Type::B:
                    updateBishopMoves(Pos(i, j));
                    break;
                case Type::R:
                    updateRookMoves(Pos(i, j));
                    break;
                case Type::N:
                    updateKnightMoves(Pos(i, j));
                    break;
                case Type::Q:
                    updateQueenMoves(Pos(i, j));
                    break;
                default:
                    updateKingMoves(Pos(i, j));
            }
        }
    }
    // Remove moves that put our own king in check
    for (auto it = legalMoves.begin(); it != legalMoves.end(); ++it) {
        move(*it); // simulate move 
        if (isKingInCheck()) legalMoves.erase(it); 
        else ++it; 
        // TO-DO: undo the move
    }
}

bool LegalBoard::move(Move m) {
    if (state != State::InPlay) return 0;
    
    if (m == RESIGN) {
        state = State::Resign;
        return 0;
    }

    bool success = 0;
    for (auto move: legalMoves) {
        if (!(move.getStart() != m.getStart()) && !(move.getEnd() != m.getEnd())) {
            success = 1;
            break;
        }
    }
    if (!success) return 0;

    int ri = m.getStart().getRank(), ci = m.getStart().getFile(), 
        rf = m.getEnd().getRank(), cf = m.getEnd().getFile(); 
    
    // handling castling permissions
    const Pos BQ = Pos{0, 0}, BK = Pos{0, 7}, WQ = Pos{7, 0}, WK = Pos{7, 7}; 
    if (sameType(ri, ci, Type::K)) {
        if (turn == Side::W) {
            castle.whiteKing = 0;
            castle.whiteQueen = 0;
        } else {
            castle.blackKing = 0;
            castle.whiteKing = 0;
        }
    } else if (sameType(ri, ci, Type::R)) {
        if (!(m.getStart() != BQ)) castle.blackQueen = 0;
        else if (!(m.getStart() != BK))castle.blackKing = 0;
        else if (!(m.getStart() != WQ)) castle.whiteQueen = 0;
        else if (!(m.getStart() != WK)) castle.whiteKing = 0;
    }

    if (!(m.getEnd() != BQ)) castle.blackQueen = 0;
    else if (!(m.getEnd() != BK)) castle.blackKing = 0;
    else if (!(m.getEnd() != WQ)) castle.whiteQueen = 0;
    else if (!(m.getEnd() != WK)) castle.whiteKing = 0;

    // Handling en passant:
    if (sameType(ri, ci, Type::P)) {
        if (ci != cf && b[rf][cf].isEmpty()) remove(Pos{ri, cf}); // remove piece captured
    // Handling updating the pawn that can potentially be captured en-passant for next turn:
        else if (ri - rf == 2 || rf - ri == 2) epMove = Pos{rf, cf};
        else epMove = NO_EN_PASSANT;
    }
    
    b[ri][ci].move(b[rf][cf]); // actually moving the piece

    // Handling promotion
    if (sameType(rf, cf, Type::P) && 
        (rf == DIM - 1 && turn == Side::B || rf == 0 && turn == Side::W)) {
        promote(m.getPromo());
    }

    // Handling the rook in castling
    if (sameType(rf, cf, Type::K) && abs(ci - cf) == 2) {
        if (!(m.getEnd() != Pos{0, 2})) b[0][0].move(b[0][3]);
        else if (!(m.getEnd() != Pos{0, 6})) b[0][7].move(b[0][5]);
        else if (!(m.getEnd() != Pos{7, 2})) b[7][0].move(b[7][3]);
        else if (!(m.getEnd() != Pos{7, 6})) b[7][7].move(b[7][5]);
    }

    turn = (turn == Side::W ? Side::B : Side::W);
    updateKingInfo();
    updateLegalMoves();
    updateState(); // WHOEVER'S TURN IT IS AT THE END MUST BE THE LOSER!!!
    return success;
}

LegalBoard::~LegalBoard() {}
