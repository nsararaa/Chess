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
                    selectPos("Destination", dest);
                }while(!isValidDst(turn));
            }while (!b.pieceAt(src)->isLegal(dest));

            int id = b.pieceAt(src)->getId();
            b.move(src, dest, window);
            b.drawBoard(window);
            b.drawBoardState(window);
            window->display();
            
            
            turnChange(turn);
            
            
            
        }
    }
    
    
    
    
};



#endif /* Chess_hpp */
