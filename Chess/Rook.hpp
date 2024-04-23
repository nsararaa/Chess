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
    
   void init(){
        tRook[0].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/wRook.png");
        tRook[1].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/bRook.png");
      
        rook[0].setTexture(tRook[0]);
        rook[1].setTexture(tRook[0]);
        rook[2].setTexture(tRook[1]);
        rook[3].setTexture(tRook[1]);
        
       for(int i=0; i < 4; i++){
           rook[i].setScale(.75f, .75f);
       }
       
       rook[0].setPosition(0, 0);
       rook[1].setPosition(700, 0);
       rook[2].setPosition(0, 700);
       rook[3].setPosition(700, 700);
       
    }
    
protected:
    void draw(sf::RenderWindow* window, int id){
        color == White?
        window->draw(rook[id]):
            window->draw(rook[id+2]);
    }
public:
    Rook(Color _col,Position _p, Board * _b, int _id): Piece(_col, _p, _id), b(_b){
        init();
    }
    
    void setBoardPos(sf::RenderWindow* window, Position dst, int id){
       if(color == White)
           rook[id].setPosition(100*dst.C, 100*dst.R);
        else
            rook[id+2].setPosition(100*dst.C, 100*dst.R);
          //
      
       // draw(window, id);
    }

    bool isLegal(Position dest);
};


#endif /* Rook_hpp */
