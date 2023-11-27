#include <iostream> 
#include "game.h"
using namespace std; 

int main() {
    string cmd; 
    LegalBoard b; 
    Game g{&b}; 

    try {
        while (cin >> cmd) {
            if (cmd == "setup") {
                if (b.getState() == State::InPlay) cout << "Game is running. Stop first" << endl;
                else {
                    while (cmd != "done") { // while in setup mode
                        if (cmd == "+") {
                            char piece; 
                            string pos; 
                            cin >> piece >> pos;
                            if (b.getTurn() == Side::W) b.place(Piece{piece, Side::W}, Pos{pos});
                            else b.place(Piece{piece, Side::B}, Pos{pos});
                        }
                        else if (cmd == "-") {
                            string pos; 
                            cin >> pos; 
                            b.remove(Pos{pos}); // remove piece from pos
                        }
                        else if (cmd == "=") {
                            string side; 
                            cin >> side; 
                            if (side == "white") b.setTurn(Side::W); 
                            else b.setTurn(Side::B); 
                        }
                    }
                    // check the board contains 1 white king, 1 black king, no pawns 
                    // on the first and last rank and that neither king is in check
                    // b.isValidPosition()
                }
            }
            else if (cmd == "game") {
                string white, black; 
                cin >> white >> black; 
                g.run(white, black);  
            }
        }  
    }
    catch (/* Exception */) {}
}