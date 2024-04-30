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
    
public:
    Chess(){
        Ps[0] = new Player("Sara", Black);
        Ps[1] = new Player("Manal", White);
        turn = White;
            
        
        VidMode.width =1400;
        VidMode.height = 800;
        window = new sf::RenderWindow(VidMode, "Chess", sf::Style::Titlebar | sf::Style::Close);
        
        if(!font.loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/Roboto-BoldItalic.ttf"))
                std::cout << "Error";
       
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
    
    Position findKing(Board b, int turn);
    bool check(Board b, int turn);
    bool isValidSrc(Position src, int turn);
    
    bool selfCheck();

    
    
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

    
    struct Move{
        Position src, dst;
    };
    
    void printMoves(std::vector <Move> moves){
        std::cout << std::endl;
        for(auto ele: moves){
            std::cout << ele.src.R << " " << ele.src.C << ", " << ele.dst.R << " " <<ele.dst.C << std::endl;
        }
    }
    void addToArray(std::vector <Move> &moves, Position s, Position d);
    void undo(std::vector <Move> &moves);
    
    
    void saveToFile(){
        std::ofstream Wtr("/Users/saranoor/Downloads/Xcode/Chess/Chess/chessState.txt");
        for(int r=0; r < 8; r++){
            for(int c=0; c <8; c++){
                Piece* piece = b.pieceAt({r, c});
                if(piece != nullptr){
                    Position p = piece->getPosition();
                    Wtr << piece->getId() << " " << (piece->getColor()== Black?'B':'W') << " " << p.R << " "<< p.C << std::endl;
                }
            }
        }
        
    }
    void loadFromFile(){
        std::ifstream Rdr("/Users/saranoor/Downloads/Xcode/Chess/Chess/chessState.txt");
        
        
        while(Rdr){
            Color color;
            char col;
            int id;
            Position p;
            Rdr >> id;
            Rdr >> col;
            Rdr >> p.R;
            Rdr >> p.C;
            Piece *piece = b.pieceAt(p);
            
            piece->setId(id);
            piece->setColor(col == 'B'? Black:White);
            piece->setPos(p);
        }
    }
    
    void undoBox(sf::RectangleShape& box, sf::Color bgCol);
    
    void printUndo();
    void displayGame();
    
    
    bool stalemate(){
        
        for(int r=0; r < 8; r++){
            for(int c =0; c < 8; c++){
                if(b.pieceAt(src)->isLegal({r,c}) && selfCheck())
                    return true;
            }
        }
        return false;
    }
    
    
    void play(){
        undoBox(undoButton, sf::Color::Yellow);
        Position kP ;
        std::vector <Move> moves;
        bool undoInitiated=false,s;
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
                            b.unhighlightCheck(kP);
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
                
//            if(selfCheck()){
//                std::cout << "Selfcheck" << std::endl;
//                undo(moves);
//            }
                
            if (check(b, turn)) {
                std::cout << "Check" << std::endl;
                turnChange(turn);
                kP = findKing(b, turn);
                turnChange(turn);
                b.highlightCheck(kP);
                b.drawBoard(window);
                b.drawBoardState(window);
                printUndo();
                window->display();
                
                //b.unhighlight(HPs);
                //displayGame();
               // undo(moves);
                //b.pieceAt(src)->
                //CHANGE LEGALITY
                
                
               // displayGame();


            }
//
                
                
                displayGame();
//

                
//
                turnChange(turn);
            }
            undoInitiated = false;
            //            if (checkmate(src) ) {
            //                std::cout << "Checkmate \nGame over." << std::endl;
            //                    window->close();}
        }
        
    }
    
    
    
    
};



#endif /* Chess_hpp */
