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
            return isVertMove(pos,dest) && (pos.R > dest.R) && ((dR == 1) || (dR == 2));
        }
        else
            return isVertMove(pos, dest) && (pos.R > dest.R) && (dR == 1);
    }
    else { // smal letters 1-2 //black
        if (isFirstMove){
            setIsFirstMove(White);
            return isVertMove(pos, dest) && (pos.R < dest.R) && ((dR == 1) || (dR == 2));
        }
        else
            return isVertMove(pos, dest) && (pos.R < dest.R) && (dR == 1);
        
    }
    return false;
}


bool Pawn::capture(Position src, Color col, bool HPs[][8]){
    if (col == Black){
        if(b->pieceAt({src.R-1, src.C+1}) !=nullptr && src.R-1 >=0 && src.C+1 < 8){
            if( b->pieceAt({src.R-1, src.C+1})->getColor() == White){
                HPs[src.R-1][src.C+1] = true;
            }
        }
        else if( b->pieceAt({src.R-1, src.C-1}) !=nullptr && src.R-1 >=0 && src.C-1 >=0)
            if( b->pieceAt({src.R-1, src.C-1})->getColor() == White){
                HPs[src.R-1][src.C-1] = true;
            }
            
    }
    else if(col == White){
        if(b->pieceAt({src.R+1, src.C+1}) !=nullptr){
            if(b->pieceAt({src.R+1, src.C+1})->getColor() == Black && src.R+1 <8 && src.C+1 < 8){
                HPs[src.R+1][src.C+1] = true;
            }
        }
        else if( b->pieceAt({src.R+1, src.C-1}) !=nullptr  && src.R+1 <8 && src.C-1 >=0){
            if( b->pieceAt({src.R+1, src.C-1})->getColor() == Black){
                    HPs[src.R+1][src.C-1] = true;
            }
        }
        
    }
    return true;
}
