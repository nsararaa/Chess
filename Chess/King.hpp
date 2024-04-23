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
protected:
    void init(){
        tKing[0].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/wKing.png");
        tKing[1].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/bKing.png");
        for(int i=0; i < 2; i++){
            king[i].setTexture(tKing[i]);
            king[i].setScale(.75f, .75f);
        }
        
        king[0].setPosition(400, 0);
        king[1].setPosition(400, 700);
    }
    
    void draw(sf::RenderWindow* window, int id){
        color == Black? window->draw(king[id+1]): window->draw(king[id]);
    }
public:

    King(Color _col,Position _p, Board * _b, int _id):b(_b),isFirstMove(true), Piece(_col, _p, _id){
        init();
    }
    
    void setBoardPos(sf::RenderWindow* window, Position dst, int id){
        if(color==White)
            king[id].setPosition(100*dst.C, 100*dst.R);
        else
            king[id+1].setPosition(100*dst.C, 100*dst.R);
       // draw(window, id);
    }

   // bool isLegal(Position dest);
};

#endif /* King_hpp */
