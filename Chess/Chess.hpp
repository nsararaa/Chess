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
    void selectPos(std::string Msg, Position& pos);
    
    Position convertPosToBoard(Position& Pos);
    Position convertPosToWindow(Position& Pos);

    void highlight(Board b, Position src, bool HPs[][8], int turn);
    void printHighlightConsole(bool HPs[][8]); //UTILITY REMOVE
    
    
    
    Position findKing(Board b, int turn){
        for(int r=0; r < 8; r++){
            for(int c=0; c < 8; c++){
                if(b.pieceAt({r,c}) != nullptr)
                    if(b.pieceAt({r,c})->amIKing() && b.pieceAt({r,c})->getColor() == turn)
                        return {r,c};
            }
        }
        return {0,0};
    }
    
    bool isValidSrc(Position src, int turn){
        if(b.pieceAt(src) != nullptr)
            return src.R <=7 && src.C <=7 && src.R >=0 && src.C >=0&& b.pieceAt(src)->getColor() == turn;
        return false;
    }

    int i =0;
    bool check(Board b, int turn){
           Position kingPos;
           turnChange(turn);
           kingPos = findKing(b, turn);
           turnChange(turn);
   
           for(int r=0; r < 8; r++){
               for(int c =0; c < 8; c++){
                   if(b.pieceAt({r,c}) != nullptr)
                       if(b.pieceAt({r,c})->isLegal(kingPos) && isValidSrc({r,c}, turn))
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

    
    struct Move{
        Position src, dst;
    };
    
    void printMoves(std::vector <Move> moves){
        std::cout << std::endl;
        for(auto ele: moves){
            std::cout << ele.src.R << " " << ele.src.C << ", " << ele.dst.R << " " <<ele.dst.C << std::endl;
        }
    }
    void addToArray(std::vector <Move> &moves, Position s, Position d){
        moves.push_back({s,d});
    }
    
    void undo(std::vector <Move> &moves, sf::RenderWindow* w){
        Move lastMove = moves.back();
        moves.pop_back();
        b.move(lastMove.dst, lastMove.src, w);
    }
    
    
    void play(){
        std::vector <Move> moves;
        bool checkB=false;
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
                    
                    
//                    if(selfCheck()){
//                        std::cout << "Selfcheck" << std::endl;
//                        continue;
//                    }
                }while(!isValidDst(turn));
                
                addToArray(moves, src, dest);
                printMoves(moves);
                
                b.unhighlight(HPs);
                
                b.drawBoard(window);
                b.drawBoardState(window);
                window->display();
            //}while (!b.pieceAt(src)->isLegal(dest));
            }while (!HPs[dest.R][dest.C]);

        
            b.move(src, dest, window);
            

//            if (check(b, turn)) {
//                std::cout << "Check" << std::endl;
//                checkB = true;
//            }

            b.drawBoard(window);
            b.drawBoardState(window);
            window->display();
           
//            if (checkmate(src)) {
//                std::cout << "Checkmate \nGame over." << std::endl;
//                window->close();
//            }
            
            turnChange(turn);
        }
    }
    
    
    
    
};



#endif /* Chess_hpp */
