#ifndef PORTAL_H
#define PORTAL_H

#include "tile.h"

class Portal : public Tile {
private:
    Tile* destination;

public:
    Portal(int row, int col, Tile* destTile);
    virtual ~Portal();

    void setDestination(Tile* destTile);
    Tile* getDestination();

    bool hasDestination(Tile* destTile) const;

    std::pair<bool, Tile*> onEnter(Character* who) override;

};

#endif // PORTAL_H
