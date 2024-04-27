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

