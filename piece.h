#ifndef __PIECE_H__
#define __PIECE_H__

enum class Type{K, Q, B, R, N, P}; 
enum class Side{W, B, N}; // white, black, no colour

class Piece {
    Type type; 
    Side side; 
    int value; // value of piece

    public: 
        Piece(Type t, Side s = Side::N); 
        Type getType(); // return type of piece
        Side getSide(); // get colour of piece
        ~Piece(); 
}; 

#endif 
