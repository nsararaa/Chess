//
//  Piece.hpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <iostream>
#include "Util.h"
#include <SFML/Graphics.hpp>

class Piece{
protected:
    
    Color color;
    Position pos;
    int id;
    
    static bool isHoriMove(Position s, Position d);
    static bool isVertMove(Position s, Position d);
    static bool isDiagMove(Position s, Position d);
    

    
private:
  

public:

    virtual void print(){
        
    }
    
    virtual void draw(sf::RenderWindow* window, int id)=0;
    Piece(Color _col,Position _p, int _id): color(_col), pos(_p), id(_id){}
    
    
    void setColor(Color _c);
    void setId(int _id);
    void setPos(Position dest);
    
    
    //GETTERS
    
    int getId();
    Color getColor();
    Position getPosition();
    
    
    
    
    virtual void setBoardPos(Position dst, int id)=0;
    virtual bool isLegal(Position dest)=0;
    virtual bool amIKing(){
        return false;
    }
    virtual bool amIPawn(){
        return false;
    }
    virtual bool capture(Position dest, Color col,bool HPs[][8]){
        return false;
    }
    
    
};
#endif /* Piece_hpp */

