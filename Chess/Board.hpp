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
//        createPieces();
//        initBoardDisplay();
    }
    
    void unhighlight( bool HPs[][8]);
    void printHighlightWindow(bool HPs[][8]);
    void drawBoard(sf::RenderWindow* window);
    void drawBoardState(sf::RenderWindow* window);
    void initBoxDisplay(sf::RectangleShape& box, sf::Color bgCol, Position p);
    void initBoardDisplay();
    
   
   

    void highlightCheck(Position kP);
    void unhighlightCheck(Position kP);
    Color getColor(int r, int c);
    Piece * pieceAt(Position src);
    
    Color calcColor(int r,int c);
    
    void move(Position s, Position d);
    
    void createPieces();

    
    bool isVerticalPathClear(Position s, Position d);
    bool isHorizontalPathClear(Position s, Position d);
    
    bool isDiagPathClear(Position s, Position d);
    
    bool isDiagLtoRPathClear(Position s, Position d);
    bool isDiagRtoLPathClear( Position s, Position d);

 
};

#endif /* Board_hpp */
