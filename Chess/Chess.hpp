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
    Board b, fake;
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
    
    sf::RectangleShape undoButton, saveButton;
    sf::Text uText, sText;
    
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
    
    bool selfCheck(Board b);

  
   

    void addToArray(std::vector <Move> &moves, Position s, Position d);
    void undo(std::vector <Move> &moves);
    
    
    void saveToFile();
    void loadFromFile();
    void Box(sf::RectangleShape& box, sf::Color bgCol, std::string S, sf::Text& t, Position p);
    
    void printBoxes();
    void displayGame();
    
    
    bool isWithinBox(Position p, Position p1, Position p2, Position p3, Position p4);

    
    bool checkmate(Position src);
    bool stalemate();
  
    
    void printCheck(bool Check, Position kP);
    int displayWelcomeScreen(sf::RenderWindow& window);
    int displayNewLoadScreen(Position& p);
    
    void displayGameOverScreen();
    void play(){
        bool undoInitiated=false, Check, SelfCheck = false, gamePlaying = true, CheckMate, save = false, New;
        char Undo = 'n', saveFile = 'n', loadFile = 'n';
        Box(undoButton, sf::Color::Yellow, "Undo", uText, {900,10});
        Box(saveButton, sf::Color::Cyan, "Save & Exit", sText, {900, 100});
        Position kP ;
        
//        19     376, 396
//        20     375, 490
//        21     568, 490
//        22     566, 395
//        23     676, 395
//        24     677, 489
//        25     869, 491
//        26     866, 399
        
        Position mouse;
        displayWelcomeScreen(*window);
        displayNewLoadScreen(mouse);
        New = isWithinBox(mouse, {376, 396}, {375, 490}, {568, 490}, {566, 395});

        window->clear();
        
      
        b.initBoardDisplay();
        if(New){
            b.createPieces();
            fake.createPieces();
           
        }
        else{
            loadFromFile();
           
        }
        displayGame();
        
        while(window->isOpen()){
           pollEvent();
            if(gamePlaying){
                turnMsg(turn);
                do{
                    do{
                        do{
                            selectPos("Source",src);
                            if(src.R == 0 && src.C >= 9){
                                undoInitiated = true;
                                undo(moves);
                                std::cout << "undo" << std::endl;
                                displayGame();
                                break;
                            }
                            if(src.R == 1 && src.C >= 9){
                                save = true;
                                saveToFile();
                                break;
                            }
                        }while(!isValidSrc(turn));
                        
                        if(undoInitiated||save)
                            break;
                        
                        highlight(fake, src, HPs, turn);
                        printHighlightConsole(HPs);
                        b.printHighlightWindow(HPs);
                        
                        displayGame();
                        
                        selectPos("Destination", dest);
                    }while(!isValidDst(turn));
                    
                    if(undoInitiated|| save)
                        break;
                    addToArray(moves, src, dest);
                    printMoves(moves);
                    b.unhighlight(HPs);
                    
                    //displayGame();
                }while (!HPs[dest.R][dest.C]);
                
                if(save)
                    break;
                
                if(!undoInitiated){
                    fake.move(src, dest);
                    
                    SelfCheck = selfCheck(fake);
                    if(SelfCheck){
                        std::cout << "Selfcheck" << std::endl;
                        Move lastMove = moves.back();
                        fake.move(lastMove.dst, lastMove.src);
                    }
                    else
                        b.move(src,dest);
                    
                    Check = check(fake, turn);
                    printCheck(Check, kP);
                    displayGame();
                    
                    if(!SelfCheck)
                        turnChange(turn);
                }
                
                undoInitiated = false;
                if (Check){
                    CheckMate =checkmate(src);
                    if (CheckMate) {
                        std::cout << "Checkmate \nGame over." << std::endl;
                        gamePlaying = false;
                        //break;
                    }
                }
                
                b.unhighlightCheck(kP);
            }
            else{
                sf::sleep(sf::seconds(1));
                displayGameOverScreen();
                sf::sleep(sf::seconds(1));
                break;
            }
        
            
        }
        
    }
    
    
    
    
    
    
    
};



#endif /* Chess_hpp */
