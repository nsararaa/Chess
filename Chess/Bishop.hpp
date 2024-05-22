//
//  Bishop.hpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#ifndef Bishop_hpp
#define Bishop_hpp

#include "Piece.hpp"
class Board;

class Bishop: public Piece{
    Board *b;
    
    sf::Texture tBishop[2];
    sf::Sprite bishop[4];
    
    
    void init();
protected:
    void draw(sf::RenderWindow* window, int id);
public:
    
    Bishop(Color _col,Position _p, Board * _b, int _id):b(_b), Piece(_col,_p,_id){
        init();
    }
    void setBoardPos(Position dst, int id);
    bool isLegal(Position dest);
    
};




#endif /* Bishop_hpp */
