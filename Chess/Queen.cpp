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
