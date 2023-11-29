#include "textdisplay.h"
#include "consts.h"
using namespace std; 

TextDisplay::TextDisplay() {} 

char TextDisplay::convertToChar(Piece p) {
    Type t = p.getType(); 
    Side s = p.getSide(); 

    switch (t) {
        case Type::K: 
            if (s == Side::B) return 'k'; 
            return 'K'; 
        case Type::Q: 
            if (s == Side::B) return 'q'; 
            return 'Q'; 
        case Type::B: 
            if (s == Side::B) return 'b'; 
            return 'B'; 
        case Type::R: 
            if (s == Side::B) return 'r'; 
            return 'R'; 
        case Type::P: 
            if (s == Side::B) return 'p'; 
            return 'P'; 
        default: 
            if (s == Side::B) return 'n'; 
            return 'N'; 
    }
}

void TextDisplay::notify(vector<Pos> v, Board &b) {
    for (Pos p: v) {
        int r = p.getRank(), c = p.getFile(); 
        const Piece* piece = b.getPiece(r, c); 
        td[r][c] = piece ? convertToChar(*piece) : '_'; 
    }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (int i = 0; i < DIM; i++) {
        out << 8 - i << " "; // print ranks
        for (int j = 0; j < DIM; j++) {
            out << td.td[i][j]; 
        }
        out << endl;
    }
    out << "  " << " abcdefgh" << endl; // print files
    return out; 
}
