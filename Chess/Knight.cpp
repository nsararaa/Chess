//
//  Knight.cpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#include "Knight.hpp"

bool Knight::isLegal(Position dest){
    int dR = abs(pos.R - dest.R);
    int dC = abs(pos.C - dest.C);
    return (((dR == 2 && dC == 1) || (dR == 1 && dC == 2)));
}

void Knight::setBoardPos(Position dst, int id){
    if(color == White)
        knight[id].setPosition(100*dst.C, 100*dst.R);
    else
        knight[id+2].setPosition(100*dst.C, 100*dst.R);
}

void Knight::draw(sf::RenderWindow* window, int id){
    color == Black? window->draw(knight[id+2]):window->draw(knight[id]);
}


void Knight::init(){
     tKnight[0].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/wKnight.png");
     tKnight[1].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/bKnight.png");
   
     knight[0].setTexture(tKnight[0]);
     knight[1].setTexture(tKnight[0]);
     knight[2].setTexture(tKnight[1]);
     knight[3].setTexture(tKnight[1]);
     
    for(int i=0; i < 4; i++){
        knight[i].setScale(.75f, .75f);
    }
    
    knight[0].setPosition(100, 0);
    knight[1].setPosition(600, 0);
    knight[2].setPosition(100, 700);
    knight[3].setPosition(600, 700);
 }
 
