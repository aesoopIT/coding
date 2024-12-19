#include "pit.h"
#include <ramp.h>

Pit::Pit(int row, int col): Tile("_", row, col)
{

}

std::pair<bool, Tile *> Pit::onEnter(Character *who)
{
    return Tile::onEnter(who);
}

bool Pit::onLeave(Tile *destTile, Character *who)
{
    Pit* p1=dynamic_cast<Pit*>(destTile);
    Ramp* r1=dynamic_cast<Ramp*>(destTile);
    if(p1 || r1) {
        return Tile::onLeave(destTile, who);
    }
    //std::cout << "Use Ramp to leave the Pit." << std::endl;
    return false;
}

