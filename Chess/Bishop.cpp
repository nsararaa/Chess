//
//  Bishop.cpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#include "Bishop.hpp"
#include "Board.hpp"


bool Bishop::isLegal(Position dest){
    return isDiagMove(pos, dest) && ( b->isDiagLtoRPathClear(pos, dest) || b->isDiagRtoLPathClear(pos, dest));
}
