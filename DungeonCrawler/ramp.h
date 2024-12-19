#ifndef RAMP_H
#define RAMP_H
#include<tile.h>

class Ramp: public Tile
{
public:
    Ramp(int row, int col);
    std::pair<bool, Tile*> onEnter(Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;

};

#endif // RAMP_H
