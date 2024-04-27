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
    
    
    void init(){
        tQueen[0].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/wQueen.png");
         tQueen[1].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/bQueen.png");
       
         for(int i=0; i < 2; i++){
             queen[i].setTexture(tQueen[i]);
             queen[i].setScale(.75f, .75f);
         }
       
         queen[0].setPosition(300, 0);
         queen[1].setPosition(300, 700);
    }
protected:
    void draw(sf::RenderWindow* window, int id){
        color == Black? window->draw(queen[id+1]): window->draw(queen[id]);
    }
public:
    Queen(Color _col,Position _p, Board * _b, int _id):b(_b), Piece(_col, _p, _id){
        init();
    }
    void setBoardPos(Position dst, int id){
        if(color ==White)
            queen[id].setPosition(100*dst.C, 100*dst.R);
        else
            queen[id+1].setPosition(100*dst.C, 100*dst.R);
    }
    
    bool isLegal(Position dest);

   
};

#endif /* Queen_hpp */
