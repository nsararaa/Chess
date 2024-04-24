//
//  Chess.hpp
//  Chess
//
//  Created by Sara Noor on 23/04/2024.
//

#ifndef Chess_hpp
#define Chess_hpp

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Board.hpp"


class Chess{
  
    Player* Ps[2];
    Position src, dest;
    int turn;
    Board b;
    bool HPs[8][8] {};
    
    //display
    sf::RenderWindow* window;
    sf::VideoMode VidMode;
    sf::Event event;
    
    sf::Texture tWelcome;
    sf::Sprite welcome;
    
public:
    Chess(){
        Ps[0] = new Player("Sara", Black);
        Ps[1] = new Player("Manal", White);
        turn = White;
            
        
        VidMode.width =1400;
        VidMode.height = 800;
        window = new sf::RenderWindow(VidMode, "Chess", sf::Style::Titlebar | sf::Style::Close);
    }
    
    
    
public:
    void pollEvent();
    void mouseInput(sf::Vector2i& mousePosition);
    
    
    bool isValidSrc(int turn);
    bool isValidDst(int turn);
    void turnMsg(int turn);
    void turnChange(int &turn);
    
    
    
    void selectPos(std::string Msg, Position& pos){
        std:: cout << "Enter " << Msg << " coordinates: ";
       // std::cin >> pos.R >> pos.C;
        //pos.R--;
        //pos.C--;
        sf::Vector2i mP;
        mouseInput(mP);
        pos.R = mP.y/100;
        pos.C = mP.x/100;
        
        
    }
    
    
    
    Position convertPosToBoard(Position& Pos) {
        Pos.C /= 100,Pos.R /=100;
        return Pos;
    }
    Position convertPosToWindow(Position& Pos) {
        Pos.R*=100, Pos.C*=100;
        return Pos;
    }
    
    
    
    void highlight(Board b, Position src, bool HPs[][8], int turn){
        for(int r=0; r < 8; r++){
            for(int c=0; c < 8; c++){
                HPs[r][c] = (b.pieceAt(src)->isLegal({r,c}));
                //HPs[r][c] = (b.pieceAt(src)->isLegal({r,c}) && b.pieceAt({r,c})->getColor()!= turn);
            }
        }

    }
    
    void printHighlightConsole(bool HPs[][8]){
        std::cout << std::endl;
        for(int r=0; r < 8; r++){
            for(int c=0; c < 8; c++){
                std::cout << HPs[r][c] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    Position findKing(Board b, int turn){
        for(int r=0; r < 8; r++){
            for(int c=0; c < 8; c++){
                if(b.pieceAt({r,c})->amIKing() && b.pieceAt({r,c})->getColor() == turn)
                    return {r,c};
            }
        }
        return {0,0};
    }
    
    bool check(Board b, int turn){
           Position kingPos;
           turnChange(turn);
           kingPos = findKing(b, turn);
           turnChange(turn);
           
           for(int r=0; r < 8; r++){
               for(int c =0; c < 8; c++){
                   if(b.pieceAt({r,c})->isLegal(kingPos) && isValidSrc(turn))
                       return true;
               }
           }
           return false;
    }
    bool selfCheck(){
        turnChange(turn);
        return check(b, turn);
    }


    
    
    bool checkmate(Position src){
        if(check(b, turn)){
            for(int r=0; r < 8; r++){
                for(int c=0; c < 8; c++){
                    if(b.pieceAt(src)->isLegal(src))
                        return false;
                }
            }
            return true;
        }
        return false;
    }

    
    
    void play(){
        
        b.drawBoard(window);
        b.drawBoardState(window);
        window->display();
        while(window->isOpen()){
           pollEvent();

            turnMsg(turn);
            do{
                do{
                    do{
                        selectPos("Source",src);
                    }while(!isValidSrc(turn));
                    
                    highlight(b, src, HPs, turn);
                    printHighlightConsole(HPs);
                    b.printHighlightWindow(HPs);
                    
                    b.drawBoard(window);
                    b.drawBoardState(window);
                    window->display();
                   
                
                    
                    
                    selectPos("Destination", dest);
                }while(!isValidDst(turn));
                b.unhighlight(HPs);
                
                b.drawBoard(window);
                b.drawBoardState(window);
                window->display();
            //}while (!b.pieceAt(src)->isLegal(dest));
            }while (!HPs[dest.R][dest.C]);

        
            b.move(src, dest, window);
            b.drawBoard(window);
            b.drawBoardState(window);
            window->display();
           
            
            
            turnChange(turn);
        }
    }
    
    
    
    
};



#endif /* Chess_hpp */
