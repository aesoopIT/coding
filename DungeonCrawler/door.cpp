#include "door.h"
#include<iostream>


Door::Door(int row, int col) : Tile("X", row, col), isOpen(false)
{

}

void Door::notify()
{
    std::cout << "Door at (" << this->getRow() << ", " << this->getCol() << ") " << std::endl;   // Debugging Hilfe

    if(isOpen){
        std::cout << "Die Tuer wird geschlossen" << std::endl;
        setTexture("X");
    }
    else{
        std::cout << "Die Tuer wird geoeffnet" << std::endl;
        setTexture("/");
    }
    isOpen =! isOpen;
}

std::pair<bool, Tile *> Door::onEnter(Character *who)
{
    if(!isOpen) {
        //std::cout << "Tuer ist geschlossen!" << std::endl;
        return std::make_pair(false, nullptr);     //Tür geschlossen
    }
    return Tile::onEnter(who);                     //Tür offen

}


