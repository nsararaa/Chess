//
//  Chess.cpp
//  Chess
//
//  Created by Sara Noor on 23/04/2024.
//

#include "Chess.hpp"

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
                sf::Vector2i mousePos;
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



void Chess::highlight(Board b, Position src, bool HPs[][8], int turn){
    for(int r=0; r < 8; r++){
        for(int c=0; c < 8; c++){
            if(b.pieceAt({r,c}) != nullptr) //square is occupied //check for opposite clr
                HPs[r][c] = (b.pieceAt(src)->isLegal({r,c}) && b.pieceAt({r,c})->getColor()!= turn);
            else //square is unoccupied
                HPs[r][c] = (b.pieceAt(src)->isLegal({r,c}));
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
