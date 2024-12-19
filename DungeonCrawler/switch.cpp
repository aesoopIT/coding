#include "switch.h"
#include <iostream>

Switch::Switch(int row, int col) : Tile("?", row, col)
{
    
}

std::pair<bool, Tile *> Switch::onEnter(Character *who)
{
    auto result = Tile::onEnter(who);       //std::pair<bool, Tile*> result = Tile::onEnter(who);
    if (result.first) {
        std::cout << "Switch activated at (" << this->getRow() << ", " << this->getCol() << ") " << std::endl;  // Debugging Hilfe
        activate();
    }
    return result;
}


