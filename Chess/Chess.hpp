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
    
    
    bool isWithinBox(Position p, Position p1, Position p2, Position p3, Position p4) {
            
        bool withinRRange = (p.R >= p1.R && p.R >= p2.R) && (p.R <= p3.R && p.R <= p4.R);
        bool withinCRange = (p.C >= p1.C && p.C <= p2.C) && (p.C <= p3.C && p.C >= p4.C);
        return withinRRange && withinCRange;
    }

    
    bool checkmate(Position src){
        bool Hp[8][8];
        turnChange(turn);
            for(int r=0; r < 8; r++){
                for(int c=0; c < 8; c++){

                    if(fake.pieceAt({r, c}) !=nullptr){
                        highlight(fake, {r,c}, Hp, turn);
                        if(fake.pieceAt({r, c})->getColor() == turn){

                            for(int rI=0; rI < 8; rI++){
                                for(int cI=0; cI < 8; cI++){
                                    if(Hp[rI][cI]){
                                        printHighlightConsole(Hp);
                                        std::cout << std::endl;

                                        
                                        if(check(fake, turn)){
                                            
                                        }
                                        else{
                                            turnChange(turn);
                                            return false;
                                        }
                                            
                                    
                                    }
                                }
                            }
                            
                            
                        }
                    }
                }
            }
            return true;
}


    bool stalemate(){
        
        for(int r=0; r < 8; r++){
            for(int c =0; c < 8; c++){
                if(fake.pieceAt(src)->isLegal({r,c}) )
                    return true;
            }
        }
        return false;
    }
  
    
    void printCheck(bool Check, Position kP){
        if(Check){
            std::cout << "Check" << std::endl;
            turnChange(turn);
            kP = findKing(b, turn);
            turnChange(turn);
            Check = true;
            
            b.highlightCheck(kP);
            b.drawBoard(window);
            b.drawBoardState(window);
            printBoxes();
            window->display();
        }
    }
    int displayWelcomeScreen(sf::RenderWindow& window) {
        sf::Texture welcomeTexture;
        if (!welcomeTexture.loadFromFile("/Users/saranoor/Downloads/Xcode/Chess/welcome.png")) {
            std::cout << "error: welcome.png" << std::endl;
            return 0;
        }

        sf::Sprite welcomeSprite;
        welcomeSprite.setTexture(welcomeTexture);
        welcomeSprite.setScale(.83, .83);
        window.clear();
        window.draw(welcomeSprite);
        window.display();

        sf::Event event;
        while (true) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    window.clear();
                    return 0;
                }
            }
        }
    }

    int displayNewLoadScreen(Position& p) {
        sf::Texture saveTexture;
        if (!saveTexture.loadFromFile("/Users/saranoor/Downloads/Xcode/Chess/newLoad.png")) {
            std::cout << "error : load or new" << std::endl;
            return 0;
        }

        sf::Sprite saveSprite;
        saveSprite.setTexture(saveTexture);
        saveSprite.setScale(.83f, .83f);
        window->clear();
        window->draw(saveSprite);
        window->display();

        sf::Event event;
        bool coordinatesEntered = false;
        

        while (window->isOpen() && !coordinatesEntered) {
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                    return 0;
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        p.R = event.mouseButton.x;
                        p.C = event.mouseButton.y;
                        coordinatesEntered = true;
                    }
                }
            }
        }
        return 0;
    }

    
    void displayGameOverScreen() {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Cyan);
        gameOverText.setPosition(window->getSize().x / 2 - gameOverText.getGlobalBounds().width / 2,
                                 window->getSize().y / 2 - gameOverText.getGlobalBounds().height / 2);

        window->clear();
        window->draw(gameOverText);
        window->display();
    }
    
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
        
      
        
        if(New){
            b.initBoardDisplay();
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
