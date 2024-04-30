//
//  Pawn.hpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#ifndef Pawn_hpp
#define Pawn_hpp

#include <iostream>

#include "Piece.hpp"

class Board;
class Pawn: public Piece{
    bool isFirstMove;
    Board *b;
    
    
    
    sf::Texture tPawn[2];
    sf::Sprite pawn[16];
    
    
    
    void init(){
        tPawn[0].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/wPawn.png");
        tPawn[1].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/bPawn.png");
        
        for(int i=0; i < 8; i++){
            pawn[i].setTexture(tPawn[0]);
            pawn[i].setScale(.75f, .75f);
            pawn[i+8].setTexture(tPawn[1]);
            pawn[i+8].setScale(.75f, .75f);
        }
        
        for(int c=0; c < 8; c++){
            pawn[c].setPosition(100*c, 100);
            pawn[c+8].setPosition(100*c, 600);
        }
    }
protected:
    void draw(sf::RenderWindow* window, int id){
        color == White?
        window->draw(pawn[id]):
            window->draw(pawn[id+8]);
    }
    
public:
    Pawn(Color _col,Position _p, Board* _b, int _id): b(_b),isFirstMove(true), Piece(_col, _p, _id){
        init();
    }
    
    void setBoardPos(Position dst, int id){

        if(color==White) pawn[id].setPosition(100*dst.C, 100*dst.R);
        else
            pawn[id+8].setPosition(100*dst.C, 100*dst.R);
    }

    void setIsFirstMove(Color col){
        if(pos.R >1 && col == White)
            isFirstMove = false;
        if(pos.R < 6 && col == Black)
            isFirstMove = false;
    }
    
    bool isLegal(Position dest);
    
    
    bool capture(Position dest, Color col, bool HPs[][8]);
    
    bool amIPawn(){
        return true;
    }

};
#endif /* Pawn_hpp */
