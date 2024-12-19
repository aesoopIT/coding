#include "ramp.h"

Ramp::Ramp(int row, int col) : Tile("<", row, col)
{

}

std::pair<bool, Tile *> Ramp::onEnter(Character *who)
{
    return Tile::onEnter(who);
}

bool Ramp::onLeave(Tile *destTile, Character *who)
{
    return Tile::onLeave(destTile,who);
}
