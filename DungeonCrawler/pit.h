#ifndef PIT_H
#define PIT_H
#include<tile.h>

class Pit: public Tile
{
public:
    Pit(int row, int col);
    std::pair<bool, Tile *> onEnter(Character *who) override;
    bool onLeave(Tile* destTile, Character* who) override;
};


#endif // PIT_H
