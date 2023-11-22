#include <string> 
#include <iostream> 
#include "legalboard.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "l1.h"
#include "l2.h"
#include "l3.h"
#include "l4.h"

class Game {
  Player *p1, *p2;
  LegalBoard b; 
  int whiteScore, blackScore; 
  void setPlayer(string player, Player* p, Side s); // initialize player type and level 

  public: 
    Game(); // based on string player type, convert
    void setupCustom(istream &in); // setup a custom board, triggered when user inputs "setup"
    void setupDefault(); // default board

    // runs the game, returns 1 if white won, 
    // 0 if black won, 2 if it was a draw
    int run(string player1, string player2);  // players are initialized when we run a game
    ~Game();
};
