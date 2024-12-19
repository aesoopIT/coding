#ifndef WALL_H
#define WALL_H

#include "tile.h"

class Wall : public Tile {
public:
    Wall(int row, int col);
    virtual ~Wall();

    bool onLeave(Tile* destTile, Character* who) override;
    std::pair<bool, Tile*> onEnter(Character* who) override;

};

#endif // WALL_H
