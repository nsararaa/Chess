//
//  Player.hpp
//  Chess
//
//  Created by Sara Noor on 23/04/2024.
//


#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include "Util.h"

class Player{
    std::string name;
    Color col;
    
public:
    Player(std::string _n, Color _c): name(_n), col(_c){}
    
    Color getColor();
    std::string getName();
};
#endif /* Player_hpp */
