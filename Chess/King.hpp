//
//  King.hpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#ifndef King_hpp
#define King_hpp
#include "Piece.hpp"


class Board;
class King: public Piece{
    bool isFirstMove;
    Board *b;
    
    
    sf::Texture tKing[2];
    sf::Sprite king[2];
    
    void init();
protected:
    
    void draw(sf::RenderWindow* window, int id);
public:

    King(Color _col,Position _p, Board * _b, int _id):b(_b),isFirstMove(true), Piece(_col, _p, _id){
        init();
    }
    
    void setBoardPos(Position dst, int id);
    bool amIKing();
    bool isLegal(Position dest);
};

#endif /* King_hpp */
