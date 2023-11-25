#ifndef __PIECE_H__
#define __PIECE_H__
#include <string>

enum class Side{W, B};
enum class Type{K, Q, B, R, N, P};
class Piece {
    Type type; 
    Side side; 

    public: 
        bool operator==(const Piece &other) const;
        Piece(Type t, Side s); 
        Piece(char piece, Side s); 
        Type getType() const; // return char of piece
        Side getSide() const; // get colour of piece
        ~Piece(); 
}; 

#endif 
