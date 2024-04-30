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
#include <fstream>

//
//901, 11
//901, 59
//998, 57
//999, 10

class Chess{
  
    Player* Ps[2];
    Position src, dest;
    int turn;
    Board b;
    bool HPs[8][8] {};
    
    
    struct Move{
        Position src, dst;
    };
    
    std::vector <Move> moves;
    //display
    sf::RenderWindow* window;
    sf::VideoMode VidMode;
    sf::Event event;
    
    sf::Texture tWelcome;
    sf::Sprite welcome;
    
    sf::Font font;
    
    sf::RectangleShape undoButton;
    sf::Text text;
    
    sf::Vector2i mousePos;
    
  
    void printMoves(std::vector <Move> moves){
        std::cout << std::endl;
        for(auto ele: moves){
            std::cout << ele.src.R << " " << ele.src.C << ", " << ele.dst.R << " " <<ele.dst.C << std::endl;
        }
    }
    
public:
    Chess();
    
    
    
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
    
    Position findKing(Board b, int turn);
    bool check(Board b, int turn);
    bool isValidSrc(Position src, int turn);
    
    bool selfCheck();

  
   

    void addToArray(std::vector <Move> &moves, Position s, Position d);
    void undo(std::vector <Move> &moves);
    
    
    void saveToFile();
    void loadFromFile();
    void undoBox(sf::RectangleShape& box, sf::Color bgCol);
    
    void printUndo();
    void displayGame();
    
    
    
    
    
    
    bool checkmate(Position src){
        if(check(b, turn)){
            for(int r=0; r < 8; r++){
                for(int c=0; c < 8; c++){
                    if(b.pieceAt({src})->isLegal({r,c}))
                        return false;
                }
            }
            return true;
        }
        return false;
    }

    
    bool stalemate(){
        
        for(int r=0; r < 8; r++){
            for(int c =0; c < 8; c++){
                if(b.pieceAt(src)->isLegal({r,c}) )
                    return true;
            }
        }
        return false;
    }
  
    
    void play(){
        undoBox(undoButton, sf::Color::Yellow);
        Position kP ;
        
        bool undoInitiated=false,s, Check;
        char Undo = 'n', saveFile = 'n', loadFile = 'n';
        
        if(loadFile == 'n'){
            b.initBoardDisplay();
            b.createPieces();
        }
        else{
            loadFromFile();
        }
        
        displayGame();
        while(window->isOpen()){
           pollEvent();
            turnMsg(turn);
            
            do{
                do{
                    do{
                        selectPos("Source",src);
                        if(src.R == 0 && src.C == 9){
                            undoInitiated = true;
                            undo(moves);
                   
                            displayGame();
                            break;
                        }
                    }while(!isValidSrc(turn));
                    
                    if(undoInitiated)
                        break;
                    
                        highlight(b, src, HPs, turn);
                        printHighlightConsole(HPs);
                        b.printHighlightWindow(HPs);
                        
                    displayGame();
                    
                        selectPos("Destination", dest);
                }while(!isValidDst(turn));
                if(undoInitiated)
                    break;
                addToArray(moves, src, dest);
                printMoves(moves);
                b.unhighlight(HPs);

                //displayGame();
            }while (!HPs[dest.R][dest.C]);

            if(!undoInitiated){
                b.move(src, dest);
                
            if(selfCheck()){
                std::cout << "Selfcheck" << std::endl;
                undo(moves);
            }
                
            if (check(b, turn)) {
                std::cout << "Check" << std::endl;
                turnChange(turn);
                kP = findKing(b, turn);
                turnChange(turn);
                Check = true;
                
                b.highlightCheck(kP);
                b.drawBoard(window);
                b.drawBoardState(window);
                printUndo();
                window->display();
                
            }

                displayGame();

                turnChange(turn);
            }
            undoInitiated = false;
            //            if (checkmate(src) ) {
            //                std::cout << "Checkmate \nGame over." << std::endl;
            //                    window->close();}
            b.unhighlightCheck(kP);
        }
        
    }
    
    
    
    
    
    
    
};



#endif /* Chess_hpp */
