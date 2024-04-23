//
//  Rook.cpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#include "Rook.hpp"
#include "Board.hpp"


bool Rook::isLegal(Position dest){
    return (isVertMove(pos, dest) && b->isVerticalPathClear(pos, dest)) || (isHoriMove(pos, dest) && b->isHorizontalPathClear(pos, dest));
}

