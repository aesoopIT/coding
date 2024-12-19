#include "portal.h"

Portal::Portal(int row, int col, Tile* destTile) : Tile( "O", row, col), destination(destTile) {}

Portal::~Portal() {}

void Portal::setDestination(Tile *destTile)
{
    destination = destTile;
}

Tile *Portal::getDestination()
{
    return destination;
}

std::pair<bool, Tile*> Portal::onEnter(Character* who) {
    return std::make_pair(true, destination);
}

bool Portal::hasDestination(Tile *destTile) const
{
    return this->destination == destTile;
}
