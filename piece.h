#ifndef __PIECE_H__
#define __PIECE_H__

enum class Side{W, B, N}; // white, black, no colour

class Piece {
    char type; 
    Side side; 

    public: 
        Piece(char t, Side s = Side::N); 
        char getType(); // return char of piece
        Side getSide(); // get colour of piece
        ~Piece(); 
}; 

#endif 
