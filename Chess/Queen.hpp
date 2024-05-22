//
//  Queen.hpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#ifndef Queen_hpp
#define Queen_hpp

#include "Piece.hpp"

class Board;

class Queen:public Piece{
    Board *b;
    
    sf::Texture tQueen[2];
    sf::Sprite queen[2];
    
    
    void init();
protected:
    void draw(sf::RenderWindow* window, int id);
public:
    
    Queen(Color _col,Position _p, Board * _b, int _id):b(_b), Piece(_col, _p, _id){
        init();
    }
    void setBoardPos(Position dst, int id);
    bool isLegal(Position dest);

   
};

#endif /* Queen_hpp */
