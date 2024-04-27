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

void Board::initBoxDisplay(sf::RectangleShape& box, sf::Color bgCol, Position p){
    box.setSize(sf::Vector2f(100.f,100.f));
    box.setFillColor(bgCol);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1.f);
    box.setPosition(p.C, p.R);
}
void Board::printHighlightWindow( bool HPs[][8]){
    for(int r =0; r < 8; r++){
        for(int c =0; c < 8; c++){
            if(HPs[r][c]){
                initBoxDisplay(board[r][c],sf::Color::Yellow,{r*100, c*100});
            }
        }
    }
}

void Board::unhighlight( bool HPs[][8]){
    sf::Color Grey(128, 128, 128);
    for(int r =0; r < 8; r++){
        for(int c =0; c < 8; c++){
            if(HPs[r][c]){
                Position p;
                p.R = r*100;
                p.C = c*100;
                if(r == 0 || r == 2||r ==4 || r==6 ){
                    if(c == 0 || c == 2||c ==4 || c==6)
                        initBoxDisplay(board[r][c],sf::Color::White, {r*100, c*100});
                    else
                        initBoxDisplay(board[r][c],Grey,{r*100, c*100});
                }
                else if(r == 1 || r == 3||r ==5 || r==7 ){
                    if(c == 1 || c == 3||c ==5 || c==7)
                        initBoxDisplay(board[r][c],sf::Color::White,{r*100, c*100});
                    else
                        initBoxDisplay(board[r][c],Grey, {r*100, c*100});
                }
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

void Board::initBoardDisplay(){
    sf::Color Grey(128, 128, 128);
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
            if(r == 0 || r == 2||r ==4 || r==6 ){
                if(c == 0 || c == 2||c ==4 || c==6)
                    initBoxDisplay(board[r][c],sf::Color::White, {r*100, c*100});
                else
                    initBoxDisplay(board[r][c],Grey,  {r*100, c*100});
            }
            else if(r == 1 || r == 3||r ==5 || r==7 ){
                if(c == 1 || c == 3||c ==5 || c==7)
                    initBoxDisplay(board[r][c],sf::Color::White, {r*100, c*100});
                else
                    initBoxDisplay(board[r][c],Grey,  {r*100, c*100});
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


bool Board::isVerticalPathClear(Position s, Position d) {
    int rS = 0, rE = 0;
    if (s.R < d.R) { /// up-> down
        rS = s.R+1; rE = d.R-1;
    }
    else if (s.R > d.R) {/// down -> up
        rS = d.R+1; rE = s.R-1;
    }
    for (int r = rS; r <= rE; r++) {
        if(Bs[r][d.R] != nullptr){ //not khali
            if(Bs[r][d.R]->getColor() == Bs[s.R][s.C]->getColor())
                return false;
            else
                return false;
        }
    }
    return true;
}

bool Board::isHorizontalPathClear(Position s, Position d) {
        int cS, cE;
        if(s.C <d.C){ /// ----------->
            cS=s.C+1; cE = d.C-1;}
        else{/// <---------
            cS=d.C+1; cE = s.C-1;} //CHECK
        for(int c= cS; c <=cE; c++){
            if(Bs[d.R][c] != nullptr)
                if(Bs[d.R][c]->getColor() == Bs[s.R][s.C]->getColor())
                return false;
            else
                return false;
        }

    return true;
}


bool Board::isDiagLtoRPathClear(Position s, Position d) {
    if (s.R < d.R) { // down towards right
        int dr = abs(d.R - s.R) ;
        for (int i = 1; i <= dr; i++) {
            if (Bs[s.R + i][s.C + i]!= nullptr){
                if(Bs[s.R + i][s.C +i]->getColor() == Bs[s.R][s.C]->getColor())
                    return false;
                else
                    return false;
            }
        }
        return true;
    }
    else { // up towards left
        int dr = abs(d.R - s.R) ;
        for (int i = 1; i <= dr; i++) {
            if (Bs[s.R - i][s.C - i]!= nullptr){
                if(Bs[s.R - i][s.C -i]->getColor() == Bs[s.R][s.C]->getColor())
                    return false;
                else
                    return false;
            }
            
        }
        return true;
    }
}
bool Board::isDiagRtoLPathClear( Position s, Position d) { //left to right
    if (s.R < d.R) { ///down towards left
        int dr = abs(d.R - s.R) ; //-1
        for (int i = 1; i <= dr; i++)
            if (Bs[s.R + i][s.C - i] != nullptr)
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


bool Board::isDiagPathClear(Position s, Position d) {
    int dr = abs(d.R - s.R);
    int dc = abs(d.C - s.C);
    
    if (s.R < d.R && s.C < d.C){
        for(int i=1; i < dr; i++){
            if(Bs[s.R+i][s.C+i] != nullptr){
                if(Bs[s.R+i][s.C+i]->getColor() == Bs[s.R][s.C]->getColor())
                   return false;
                else
                   return false;
            }
        }
    }
    else if (s.R > d.R && s.C < d.C) {
        for(int i=1; i < dr; i++){
            if(Bs[s.R-i][s.C+i] != nullptr){
                if(Bs[s.R-i][s.C+i]->getColor() == Bs[s.R][s.C]->getColor())
                   return false;
                else
                   return false;
            }
        }
    }
    else if (s.R > d.R && s.C > d.C) {
        for(int i=1; i < dr; i++){
            if(Bs[s.R-i][s.C-i] != nullptr){
                if(Bs[s.R-i][s.C-i]->getColor() == Bs[s.R][s.C]->getColor())
                   return false;
                else
                   return false;
            }
        }
    }
    else if (s.R < d.R && s.C > d.C){
        for(int i=1; i < dr; i++){
            if(Bs[s.R+i][s.C-i] != nullptr){
                if(Bs[s.R+i][s.C-i]->getColor() == Bs[s.R][s.C]->getColor())
                   return false;
                else
                   return false;
            }
        }
    }
    return true;
}




Color Board::getColor(int r, int c){
    return Bs[r][c]->getColor();
}
Piece * Board::pieceAt(Position src){ //get Piece
    return Bs[src.R][src.C];
}

Color Board::calcColor(int r,int c){
    if(r == 0 || r == 2||r ==4 || r==6 ){
        if(c == 0 || c == 2||c ==4 || c==6)
            return White;
        else
            return Black;
    }
    else if(r == 1 || r == 3||r ==5 || r==7 ){
        if(c == 1 || c == 3||c ==5 || c==7)
            return White;
        else
            return Black;
    }
    return White;
}


void Board::move(Position s, Position d){
    sf::Color Grey(128, 128, 128);
    
    Bs[s.R][s.C]->setBoardPos(d, Bs[s.R][s.C]->getId());

    Bs[d.R][d.C] = Bs[s.R][s.C];
    Bs[s.R][s.C]->setPos(d);

    Bs[s.R][s.C] = nullptr;
}
