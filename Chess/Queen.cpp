//
//  Queen.cpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#include "Queen.hpp"
#include "Board.hpp"


bool Queen::isLegal(Position dest){
    return ((isVertMove(pos, dest) && b->isVerticalPathClear(pos, dest)) || (isHoriMove(pos, dest) && b->isHorizontalPathClear(pos, dest))) || (isDiagMove(pos, dest) && (b->isDiagPathClear(pos, dest)));
}

void Queen::setBoardPos(Position dst, int id){
    if(color ==White)
        queen[id].setPosition(100*dst.C, 100*dst.R);
    else
        queen[id+1].setPosition(100*dst.C, 100*dst.R);
}

void Queen::draw(sf::RenderWindow* window, int id){
    color == Black? window->draw(queen[id+1]): window->draw(queen[id]);
}

void Queen::init(){
    tQueen[0].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/wQueen.png");
     tQueen[1].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/bQueen.png");
   
     for(int i=0; i < 2; i++){
         queen[i].setTexture(tQueen[i]);
         queen[i].setScale(.75f, .75f);
     }
   
     queen[0].setPosition(300, 0);
     queen[1].setPosition(300, 700);
}
