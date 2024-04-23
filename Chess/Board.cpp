//
//  Board.cpp
//  Chess
//
//  Created by Sara Noor on 23/04/2024.
//

#include "Board.hpp"


void Board::drawBoardState(sf::RenderWindow* window){
  //  initBoardDisplay();
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
            if(Bs[r][c] !=nullptr){
                Bs[r][c]->draw(window, Bs[r][c]->getId());
              
            }
        }
    }
}


void Board::drawBoard(sf::RenderWindow* window){
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
            window->draw(board[r][c]);
        }
    }
}
void Board::initBoxDisplay(sf::RectangleShape& box, sf::Color bgCol, sf::Color outLineCol, Position p){
    box.setSize(sf::Vector2f(100.f,100.f));
    box.setFillColor(bgCol);
    box.setOutlineColor(outLineCol);
    box.setPosition(p.R, p.C);
}
void Board::initBoardDisplay(){
    sf::Color Grey(128, 128, 128);
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
            if(r == 0 || r == 2||r ==4 || r==6 ){
                if(c == 0 || c == 2||c ==4 || c==6)
                    initBoxDisplay(board[r][c],sf::Color::White, sf::Color::Black, {r*100, c*100});
                else
                    initBoxDisplay(board[r][c],Grey, sf::Color::White, {r*100, c*100});
            }
            else if(r == 1 || r == 3||r ==5 || r==7 ){
                if(c == 1 || c == 3||c ==5 || c==7)
                    initBoxDisplay(board[r][c],sf::Color::White, sf::Color::White, {r*100, c*100});
                else
                    initBoxDisplay(board[r][c],Grey, sf::Color::Black, {r*100, c*100});
            }
        }
    }
}


void Board::createPieces(){
    
    int rIdw,rIdb, kIdw,kIdb, qIdw,qIdb, hIdw, hIdb, bIdw, bIdb, pIdw, pIdb;
    rIdw= rIdb = kIdb = kIdw = qIdb = qIdw = hIdw = hIdb = bIdb = bIdw= pIdb = pIdw =0;
    
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
            if(r ==1){
                Bs[r][c] = new Pawn(White,{r,c},this, pIdw++);
            }
            if(r ==6){
                Bs[r][c] = new Pawn(Black, {r,c},this, pIdb++);
            }
            if(r==0 && (c== 0 || c ==7)){
                Bs[r][c] = new Rook(White, {r,c},this, rIdw++);
            }
            if(r==7 && (c== 0 || c ==7)){
                Bs[r][c] = new Rook(Black, {r,c},this, rIdb++);
            }
            if(r==0 && (c== 1 || c ==6)){
                Bs[r][c] = new Knight(White, {r,c},this, hIdw++);
            }
            if(r==7 && (c== 1 || c ==6)){
                Bs[r][c] = new Knight(Black, {r,c},this, hIdb++);
            }
            if(r==0 && (c== 2 || c ==5)){
                Bs[r][c] = new Bishop(White, {r,c},this, bIdw++);
            }
            if(r==7 && (c== 2 || c ==5)){
                Bs[r][c] = new Bishop(Black, {r,c},this, bIdb++);
            }
            if(r==0 && c== 3){
                Bs[r][c] = new Queen(White, {r,c},this, qIdw++);
            }
            if(r==7 && c== 3){
                Bs[r][c] = new Queen(Black, {r,c},this, qIdb++);
            }
            if(r==0 && c== 4){
                Bs[r][c] = new King(White, {r,c},this, kIdw++);
            }
            if(r==7 && c== 4){
                Bs[r][c] = new King(Black, {r,c},this, kIdb++);
            }
            
        }
    }
    
}



 bool Board::isVerticalPathClear(Position s, Position d){
     int start, end;
     if(s.R < d.R){
        start = s.R +1;
        end = d.R -1;}
    else {
        start = s.R -1;
        end = d.R +1;}
     
     for(int r = start; r <= end; r++)
         if(Bs[r][d.C] != nullptr)
             return false;
     return true;

}
bool Board::isHorizontalPathClear(Position s, Position d){
    int start, end;
    if(s.C < d.C){
       start = s.C +1;
       end = d.C -1;}
   else {
       start = s.C -1;
       end = d.C +1;}
    
    for(int c = start; c <= end; c++)
        if(Bs[d.R][c] != nullptr)
            return false;
    return true;

}

bool Board::isDiagLtoRPathClear(Position s, Position d) {
    if (s.R < d.R) { // down towards right
        int dr = abs(d.R - s.R) ;
        for (int i = 1; i <= dr; i++) //
            if ( Bs[s.R + i][s.C + i]!= nullptr)
                return false;
        return true;
    }
    else { // up towards left
        int dr = abs(d.R - s.R) ;
        for (int i = 1; i <= dr; i++) {
            if (Bs[s.R - i][s.C - i]!= nullptr)
                return false;
            
        }
        return true;
    }
}
bool Board::isDiagRtoLPathClear( Position s, Position d) { //left to right
    if (s.R < d.R) { ///down towards left
        int dr = abs(d.R - s.R) ; //-1
        for (int i = 1; i <= dr; i++)
            if ( Bs[s.R + i][s.C - i] != nullptr)
                return false;
        return true;
    }
    else {/// up towards right
        int dr = abs(d.R - s.R) ; //-1
        for (int i = 1; i <= dr; i++)
            if ( Bs[s.R - i][s.C + i] != nullptr)
                return false;
        return true;
    }
}
