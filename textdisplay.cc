#include "textdisplay.h"
using namespace std; 

TextDisplay::TextDisplay() {} 

void TextDisplay::notify(Board &b) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            td[i][j] = b.getPiece(i, j); 
        }
    }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (int i = 0; i < 8; i++) {
        out << 8 - i << " "; // print ranks
        for (int j = 0; j < 8; j++) {
            out << td[i][j]; 
        }
        out << endl;
    }

    out << "  "; 
    for (int i = 0; i < 8; i++) { // print files
        char c = i + 'a';
        out << c << endl; 
    }
    return out; 
}
