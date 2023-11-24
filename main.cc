#include <iostream> 
using namespace std; 

void printScore(int w, int b) {
    cout << "Final Score: " << endl;
    cout << "White: " << w << endl; 
    cout << "Black: " << b << endl; 
}

int main() {
    // controls multiple teams 

    int whiteScore = 0, blackScore = 0; 

    while () { // not eof
        LegalBoard b; 
        Player *p1, *p2; 
        string cmd; 
        while (cin >> cmd) {
            if (cmd == "game") {
                string w, b; 
                cin >> w >> b; 
                if (w == "human") continue; 
                else {
                    char lvl = w.back(); 
                    if (lvl == '1') {

                    }
                    else if (lvl == '2') {

                    }
                    else if (lvl == '3') {

                    }
                    else {}
                }
            }
            else if (cmd == "resign") {
                b.getScore
            }
            else if (cmd == "move") {
                // if computer, automatically move 
                
                // if human, take in start and end moves
                string start, end; 
                cin >> start >> end; 
                b.move(Move{Pos{start}, Pos{end}}); 

                // if move enables a pawn promotion, take in piece to promote to
                // Q: how can we check the number of parameters in the line?
                string promoteTo; 
                cin >> promoteTo;
                b.move(start, end, promoteTo); 
            }
            else if (cmd == "setup") {
                // check game is not currently running 

                char op; 
                while (cin >> op) {
                    if (op == '+') {
                        char piece; 
                        string pos; 
                        cin >> piece >> pos; 
                        b.place(Piece{piece}, Pos{pos});
                    }
                    else if (op == '-') {
                        string pos; 
                        cin >> pos; 
                        b.remove(Pos{pos}) // remove piece from pos
                    }
                    else if (op == '=') {
                        string side; 
                        cin >> side; 
                        // side's turn next
                        if (side == 'white') b.setTurn(Side::W); 
                        else b.setTurn(Side::B); 
                    }
                    else break; // done
                }
            }
        }  
    }

    printScore(whiteScore, blackScore); 

}