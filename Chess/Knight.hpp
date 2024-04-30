//
//  Knight.hpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#ifndef Knight_hpp
#define Knight_hpp

#include "Piece.hpp"

class Board;

class Knight:public Piece{
    sf::Texture tKnight[2];
    sf::Sprite knight[4];
    Board *b;
    
    void init();
protected:
    void draw(sf::RenderWindow* window, int id);
public:
    Knight(Color _col,Position _p, Board * _b, int _id): Piece(_col, _p, _id), b(_b){
        init();
    }
    
    void setBoardPos(Position dst, int id);
    bool isLegal(Position dest);
};


#endif /* Knight_hpp */
