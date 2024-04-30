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
    
    void init();
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
    
    void setBoardPos(Position dst, int id);
    void setIsFirstMove(Color col);
    
    bool isLegal(Position dest);
    
    
    bool capture(Position dest, Color col, bool HPs[][8]);
    
    bool amIPawn(){
        return true;
    }

};
#endif /* Pawn_hpp */
