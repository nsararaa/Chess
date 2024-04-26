//
//  Pawn.cpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#include "Pawn.hpp"
#include "Board.hpp"


bool Pawn::isLegal(Position dest){
    int dR = abs(pos.R - dest.R);
    if (b->pieceAt(pos)->getColor() == Black) {
        if (isFirstMove){ //first move
            setIsFirstMove(Black);
            //isFirstMove = false;
            return isVertMove(pos,dest) && (pos.R > dest.R) && ((dR == 1) || (dR == 2));
        }
        else
            return isVertMove(pos, dest) && (pos.R > dest.R) && (dR == 1);
    }
    else { // smal letters 1-2 //black
        if (isFirstMove){
            setIsFirstMove(White);
           // isFirstMove = false;
            return isVertMove(pos, dest) && (pos.R < dest.R) && ((dR == 1) || (dR == 2));
        }
        else
            return isVertMove(pos, dest) && (pos.R < dest.R) && (dR == 1);
        
    }
    
}
