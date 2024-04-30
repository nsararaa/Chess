//
//  King.cpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#include "King.hpp"
#include "Board.hpp"


bool King::isLegal(Position dest){
    int dR = abs(pos.R - dest.R);
    int dC = abs(pos.C - dest.C);
    return ( ((isVertMove(pos, dest) && b->isVerticalPathClear(pos, dest)) || (isHoriMove(pos, dest) && b->isHorizontalPathClear(pos, dest))) || (isDiagMove(pos, dest) && (b->isDiagPathClear(pos, dest)))) && dR <= 1 && dC <= 1;
    
}


void King::init(){
    tKing[0].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/wKing.png");
    tKing[1].loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/pieces-basic-png/bKing.png");
    for(int i=0; i < 2; i++){
        king[i].setTexture(tKing[i]);
        king[i].setScale(.75f, .75f);
    }
    
    king[0].setPosition(400, 0);
    king[1].setPosition(400, 700);
}

void King::draw(sf::RenderWindow* window, int id){
    color == Black? window->draw(king[id+1]): window->draw(king[id]);
}


void King::setBoardPos(Position dst, int id){
    if(color==White)
        king[id].setPosition(100*dst.C, 100*dst.R);
    else
        king[id+1].setPosition(100*dst.C, 100*dst.R);
}

bool King::amIKing(){
    return true;
}
