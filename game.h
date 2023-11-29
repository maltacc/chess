#ifndef __GAME_H__
#define __GAME_H__

#include <string> 
#include <iostream> 
#include "legalBoard.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "l1.h"
#include "l2.h"
#include "l3.h"
#include "l4.h"

class Game {
  LegalBoard *b;
  Player *wp, *bp; // white player, black player
  float whiteScore, blackScore; 
  void setPlayer(string player, Player* p); // initialize player type and level 

  public: 
    Game(LegalBoard* b); // based on string player type, convert
    void setupCustom(istream &in); // setup a custom board, triggered when user inputs "setup"
    void setupDefault(); // default board

    // run a single iteration of the game
    void run(string wplayer, string bplayer);  // players are initialized when we run a game
    ~Game();

    friend ostream& operator<<(ostream &out, const Game &g); 
};

#endif
