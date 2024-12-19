#include "floor.h"

Floor::Floor(int row, int col) : Tile(".", row, col) {}

Floor::~Floor() {}

bool Floor::onLeave(Tile* destTile, Character* who)  {
    return true;
}

std::pair<bool, Tile *> Floor::onEnter(Character *who)
{
    return std::make_pair(true, nullptr);
}
