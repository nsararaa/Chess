//
//  Piece.cpp
//  Chess
//
//  Created by Sara Noor on 23/04/2024.
//

#include "Piece.hpp"

void Piece::setColor(Color _c){
    color = _c;
}
void Piece::setId(int _id){
    id = _id;
}
void Piece::setPos(Position dest){
    pos=dest;
}


//GETTERS

int Piece::getId(){
    return id;
}
Color Piece::getColor(){
    return color;
}
Position Piece::getPosition(){
    return pos;
}


 bool Piece::isHoriMove(Position s, Position d){
     return s.R == d.R && s.C != d.C;
 }
bool Piece::isVertMove(Position s, Position d){
     return s.C == d.C && s.R != d.R;
 }
bool Piece::isDiagMove(Position s, Position d){
     Position delta;
     delta.R = d.R-s.R;
     delta.C = d.C-s.C;
     return abs(delta.R) == abs(delta.C);
 }
// static bool isEmpty(Position p){
//     return true;
// }
//
