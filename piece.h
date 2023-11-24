#ifndef __PIECE_H__
#define __PIECE_H__
#include <string>

enum class Side{W, B};
enum class Type{K, Q, B, R, N, P};
class Piece {
    Type type; 
    Side side; 

    public: 
        Piece(Type t, Side s); 
        Piece(char piece, Side s); 
        Type getType(); // return char of piece
        Side getSide(); // get colour of piece
        ~Piece(); 
}; 

#endif 
