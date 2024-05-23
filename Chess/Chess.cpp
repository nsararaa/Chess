//
//  Chess.cpp
//  Chess
//
//  Created by Sara Noor on 23/04/2024.
//

#include "Chess.hpp"


Chess::Chess(){
    Ps[0] = new Player("Sara", Black);
    Ps[1] = new Player("Manal", White);
    turn = White;
        
    
    VidMode.width =1400;
    VidMode.height = 800;
    window = new sf::RenderWindow(VidMode, "Chess", sf::Style::Titlebar | sf::Style::Close);
    
    if(!font.loadFromFile("/Users/saranoor/Downloads/Xcode/Chess disp/Roboto-BoldItalic.ttf"))
            std::cout << "Error";
   
}

void Chess::mouseInput(sf::Vector2i& mousePosition){
    bool mouseInput = false;
       while (!mouseInput) {
           while (window->pollEvent(event)) {
               if (event.type == sf::Event::Closed) {
                   window->close();
               }

               if (event.type == sf::Event::MouseButtonPressed) {
                   mousePosition = sf::Mouse::getPosition(*window);
                   mouseInput = true;
               }
           }
       }
}


void Chess::pollEvent(){
    while(window->pollEvent(event)){ //basically saves all the events from window in variable event
        switch(event.type){
            case sf::Event::Closed:
                window->close();
                //                case sf::Event::Resized:
                //                    <#code#>
                //                    break;
                //                case sf::Event::LostFocus:
                //                    <#code#>
                //                    break;
                //                case sf::Event::GainedFocus:
                //                    <#code#>
                //                    break;
                //                case sf::Event::TextEntered:
                //                    <#code#>
                //                    break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
                //                case sf::Event::KeyReleased:
                //                    <#code#>
                //                    break;
            case sf::Event::MouseButtonPressed:
                
                sf::Mouse::getPosition(*window);
                std::cout<< mousePos.x<< ", "<< mousePos.y<< std::endl;
//                    bishop[0].setPosition(mousePos.x, mousePos.y);
                break;
            
        }
    }
}


void Chess::turnMsg(int turn) {
    std::cout << Ps[turn]->getName() << "'s (" << (Ps[turn]->getColor() == Black ? "Black" : "White") << ") turn: " << std::endl;
}

bool Chess::isValidSrc(int turn){
    if(b.pieceAt(src) != nullptr)
        return src.R <=7 && src.C <=7 && src.R >=0 && src.C >=0&& b.pieceAt(src)->getColor() == turn;
    return false;
}

bool Chess::isValidDst(int turn){
    if(b.pieceAt(dest) != nullptr){
        return dest.R <=7 && dest.C <=7 && dest.R >=0 && dest.C >=0 && b.pieceAt(dest)->getColor()!= turn;
    }
    return dest.R <=7 && dest.C <=7 && dest.R >=0 && dest.C >=0;
}

void Chess::turnChange(int &turn){
    turn == White? turn =Black: turn =White;
}






void Chess::selectPos(std::string Msg, Position& pos){
    std:: cout << "Enter " << Msg << " coordinates: ";
   // std::cin >> pos.R >> pos.C;
    //pos.R--;
    //pos.C--;
    sf::Vector2i mP;
    mouseInput(mP);
    pos.R = mP.y/100;
    pos.C = mP.x/100;
    
    
}



Position Chess::convertPosToBoard(Position& Pos) {
    Pos.C /= 100,Pos.R /=100;
    return Pos;
}
Position Chess::convertPosToWindow(Position& Pos) {
    Pos.R*=100, Pos.C*=100;
    return Pos;
}


bool Chess::check(Board b, int turn){
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


void Chess::highlight(Board b, Position src, bool HPs[][8], int turn){
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
          
            
            if(b.pieceAt({r,c}) != nullptr) //square is occupied //check for opposite clr
                HPs[r][c] = (b.pieceAt(src)->isLegal({r,c}) && b.pieceAt({r,c})->getColor()!= turn);
            else //square is unoccupied
                HPs[r][c] = (b.pieceAt(src)->isLegal({r,c}));
            
            if(b.pieceAt(src)->amIPawn()){
                b.pieceAt(src)->capture(src, b.pieceAt(src)->getColor(), HPs);
            }
            
            
        }
    }
    
    

}

void Chess::printHighlightConsole(bool HPs[][8]){
    std::cout << std::endl;
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
            std::cout << HPs[r][c] << " ";
        }
        std::cout << std::endl;
    }
}




Position Chess::findKing(Board b, int turn){
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
            if(b.pieceAt({r,c}) != nullptr)
                if(b.pieceAt({r,c})->amIKing() && b.pieceAt({r,c})->getColor() == turn)
                    return {r,c};
        }
    }
    return {0,0};
}

bool Chess::isValidSrc(Position src, int turn){
    if(b.pieceAt(src) != nullptr)
        return src.R <=7 && src.C <=7 && src.R >=0 && src.C >=0&& b.pieceAt(src)->getColor() == turn;
    return false;
}

int i =0;

bool Chess::selfCheck(Board b){
    turnChange(turn);
    bool sc = check(b,turn);
    turnChange(turn);
    return sc;
}



void Chess::Box(sf::RectangleShape& undo, sf::Color bgCol, std::string S, sf::Text& t, Position p){
    undo.setSize(sf::Vector2f(150,50.f));
    undo.setPosition(p.R, p.C);
    undo.setFillColor(bgCol);
    
    
    t.setFont(font);
    t.setString(S);
    t.setCharacterSize(24);
      t.setFillColor(sf::Color::Black);
    t.setPosition(p.R + 20, p.C +10);
}



void Chess::printBoxes(){
    window->draw(undoButton);
    window->draw(saveButton);
    window->draw(uText);
    window->draw(sText);
}

void Chess::displayGame(){
    b.drawBoard(window);
    b.drawBoardState(window);
    printBoxes();
    window->display();
}


void Chess::addToArray(std::vector <Move> &moves, Position s, Position d){
    if((s.R != 0 && s.C < 9) || (s.R != 1 && s.C < 9)) //undo coordinates
        moves.push_back({s,d});
}

void Chess::undo(std::vector <Move> &moves){
    if(moves.size() <=0)
        return;
    Move lastMove = moves.back();
    moves.pop_back();
    b.move(lastMove.dst, lastMove.src);
    
    turnChange(turn);
}
















void writePiece(Piece* piece, std::ofstream& Wtr) {
    if (King* king = dynamic_cast<King*>(piece)) {
        Wtr << 'k';
    } else if (Queen* queen = dynamic_cast<Queen*>(piece)) {
        Wtr << 'q';
    } else if (Knight* knight = dynamic_cast<Knight*>(piece)) {
        Wtr << 'n';
    } else if (Bishop* bishop = dynamic_cast<Bishop*>(piece)) {
        Wtr << 'b';
    } else if (Rook* rook = dynamic_cast<Rook*>(piece)) {
        Wtr << 'r';
    } else if (Pawn* pawn = dynamic_cast<Pawn*>(piece)) {
        Wtr << 'p';
    }
    
}





bool Chess::isWithinBox(Position p, Position p1, Position p2, Position p3, Position p4) {
        
    bool withinRRange = (p.R >= p1.R && p.R >= p2.R) && (p.R <= p3.R && p.R <= p4.R);
    bool withinCRange = (p.C >= p1.C && p.C <= p2.C) && (p.C <= p3.C && p.C >= p4.C);
    return withinRRange && withinCRange;
}


bool Chess::checkmate(Position src){
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


bool Chess::stalemate(){
    
    for(int r=0; r < 8; r++){
        for(int c =0; c < 8; c++){
            if(fake.pieceAt(src)->isLegal({r,c}) )
                return true;
        }
    }
    return false;
}


void Chess::printCheck(bool Check, Position kP){
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
int Chess::displayWelcomeScreen(sf::RenderWindow& window) {
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

int Chess::displayNewLoadScreen(Position& p) {
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


void Chess::displayGameOverScreen() {
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





void Chess::saveToFile(){
    std::ofstream Wtr("/Users/saranoor/Downloads/Xcode/Chess/Chess/chessState.txt");
    
 
    for(int r=0; r < 8; r++){
        for(int c=0; c <8; c++){
            Piece* piece = b.pieceAt({r, c});
            if(piece != nullptr){
                Position p = piece->getPosition();
                writePiece(piece, Wtr);
                Wtr << " "<< piece->getId() << " " << (piece->getColor()== Black?'B':'W') << " " << p.R << " "<< p.C << std::endl;
            }
        }
    }
    
}
void Chess::loadFromFile() {
    std::ifstream Rdr("/Users/saranoor/Downloads/Xcode/Chess/Chess/chessState.txt");
    if (!Rdr) {
        std::cerr << "error: opening file" << std::endl;
        return;
    }

    char pieceType;
    int id, row, col;
    char colorChar;
    Color c;
    while (Rdr) {
        Rdr >> pieceType >> id >> colorChar >> row >> col;
        c = (colorChar == 'B') ? Black : White;
        
        b.initFilePieces(pieceType, row, col, c, id);
        fake.initFilePieces(pieceType, row, col, c, id);
    }
//    window->clear();
//    b.drawBoard(window);
//    b.drawBoardState(window);
//    std::cout << 'y';
    
}

