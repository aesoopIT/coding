#include "wall.h"

Wall::Wall(int row, int col) : Tile("#", row, col) {}

Wall::~Wall() {}

bool Wall::onLeave(Tile* destTile, Character* who) {
    return false;
}

std::pair<bool, Tile *> Wall::onEnter(Character *who)
{
    return std::make_pair(false, nullptr);
}
