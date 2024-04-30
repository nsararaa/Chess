//
//  Rook.hpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#ifndef Rook_hpp
#define Rook_hpp

#include "Piece.hpp"

class Board;



class Rook:public Piece{
    sf::Texture tRook[2];
    sf::Sprite rook[4];
    
    Board *b;
    
    void init();
protected:
    void draw(sf::RenderWindow* window, int id);
public:
    Rook(Color _col,Position _p, Board * _b, int _id): Piece(_col, _p, _id), b(_b){
        init();
    }
    
    void setBoardPos(Position dst, int id);

    bool isLegal(Position dest);
};


#endif /* Rook_hpp */
