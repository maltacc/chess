#include <iostream> 
#include "game.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std; 

int main() {
    string cmd; 
    LegalBoard b; 
    TextDisplay *td; 
    GraphicsDisplay *gd; 
    Game g{&b}; 
    b.attach(td);
    b.attach(gd); 

    while (cin >> cmd) {
        if (cmd == "setup") {
            if (b.getState() == State::InPlay) 
                cout << "Game is running. Stop first" << endl;
            else {
                string setCmd; 
                while (cin >> setCmd && setCmd != "done") { // while in setup mode
                    if (setCmd == "+") {
                        char piece; 
                        string pos; 
                        cin >> piece >> pos;
                        if (b.getTurn() == Side::W) b.place(Piece{piece}, Pos{pos});
                        else b.place(Piece{piece}, Pos{pos});
                    }
                    else if (setCmd == "-") {
                        string pos; 
                        cin >> pos; 
                        b.remove(Pos{pos}); // remove piece from pos
                    }
                    else if (setCmd == "=") {
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
        else cout << "Invalid command" << endl; 
    }

    cout << g << endl;  // print score at the end of the program 
}

