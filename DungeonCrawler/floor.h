#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"

class Floor : public Tile {
public:
    Floor(int row, int col);
    virtual ~Floor();

    bool onLeave(Tile* destTile, Character* who) override;
    std::pair<bool, Tile*> onEnter(Character* who) override;

};

#endif // FLOOR_H
