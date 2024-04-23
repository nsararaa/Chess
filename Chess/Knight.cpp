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
