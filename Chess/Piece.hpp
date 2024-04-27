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
    
   static bool isHoriMove(Position s, Position d){
        return s.R == d.R && s.C != d.C;
    }
    static bool isVertMove(Position s, Position d){
        return s.C == d.C && s.R != d.R;
    }
    static bool isDiagMove(Position s, Position d){
        Position delta;
        delta.R = d.R-s.R;
        delta.C = d.C-s.C;
        return abs(delta.R) == abs(delta.C);
    }
    static bool isEmpty(Position p){
        return true;
    }
    

    
private:
  

public:

    virtual void print(){
        
    }
    
    virtual void draw(sf::RenderWindow* window, int id)=0;
    Piece(Color _col,Position _p, int _id): color(_col), pos(_p), id(_id){}
    
    
    void setColor(Color _c){
        color = _c;
    }
    void setId(int _id){
        id = _id;
    }
    void setPos(Position dest){
        pos=dest;
    }
    
    
    //GETTERS
    
    int getId(){
        return id;
    }
    Color getColor(){
        return color;
    }
    Position getPosition(){
        return pos;
    }
    
    
    
    
    virtual void setBoardPos(Position dst, int id)=0;
    virtual bool isLegal(Position dest)=0;
    virtual bool amIKing(){
        return false;
    }
    
    
};
#endif /* Piece_hpp */

