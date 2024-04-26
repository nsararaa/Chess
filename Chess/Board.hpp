//
//  Board.hpp
//  Chess OOP
//
//  Created by Sara Noor on 19/04/2024.
//

#ifndef Board_hpp
#define Board_hpp

#include "Pawn.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Util.h"

class Piece;

class Board{
    Piece *Bs[8][8] {};
    
    
    sf::RectangleShape box;
    sf::RectangleShape board[8][8];
    
public:
    Board(){
        createPieces();
        initBoardDisplay();
    }
    
    void unhighlight( bool HPs[][8]);
    void printHighlightWindow(bool HPs[][8]);
    void drawBoard(sf::RenderWindow* window);
    void drawBoardState(sf::RenderWindow* window);
    void initBoxDisplay(sf::RectangleShape& box, sf::Color bgCol, Position p);
    void initBoardDisplay();
    
   
   

   
    Color getColor(int r, int c){
        return Bs[r][c]->getColor();
    }
    Piece * pieceAt(Position src){ //get Piece
        return Bs[src.R][src.C];
    }
    
    Color calcColor(int r,int c){
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
    
    
    void move(Position s, Position d,sf::RenderWindow* window){
        sf::Color Grey(128, 128, 128);
      //  initBoxDisplay(box, calcColor(s.R--, s.C--)==White? sf::Color::White:Grey, sf::Color::Black, s);
  
        Bs[s.R][s.C]->setBoardPos(window, d, Bs[s.R][s.C]->getId());

        Bs[d.R][d.C] = Bs[s.R][s.C];
        Bs[s.R][s.C]->setPos(d);

        //window->display();
        Bs[s.R][s.C] = nullptr;
    }
    
    void createPieces();

    
    bool isVerticalPathClear(Position s, Position d);
    bool isHorizontalPathClear(Position s, Position d);
    
    bool isDiagLtoRPathClear(Position s, Position d);
    bool isDiagRtoLPathClear( Position s, Position d);

 
};

#endif /* Board_hpp */
