//
//  Bishop.cpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#include "Bishop.hpp"
#include "Board.hpp"


bool Bishop::isLegal(Position dest){
    return ((isDiagMove(pos, dest)) && (b->isDiagPathClear(pos, dest)));
}

void Bishop::setBoardPos(Position dst, int id){
    if(color == White)
        bishop[id].setPosition(100*dst.C, 100*dst.R);
    else
        bishop[id+2].setPosition(100*dst.C, 100*dst.R);
}

void Bishop::draw(sf::RenderWindow* window, int id){
    color == White?
    window->draw(bishop[id]):
        window->draw(bishop[id+2]);
}


void Bishop::init(){
    tBishop[0].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/wBishop.png");
    tBishop[1].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/bBishop.png");
    
    bishop[0].setTexture(tBishop[0]);
    bishop[1].setTexture(tBishop[0]);
    bishop[2].setTexture(tBishop[1]);
    bishop[3].setTexture(tBishop[1]);
    
    
      
      bishop[0].setPosition(200, 0);
      bishop[1].setPosition(500, 0);
      bishop[2].setPosition(200, 700);
      bishop[3].setPosition(500, 700);
 
    for(int i=0; i < 4; i++){
        bishop[i].setScale(.75f, .75f);
    }
}
