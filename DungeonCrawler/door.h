#ifndef DOOR_H
#define DOOR_H

#include<tile.h>
#include<passive.h>

class Door : public Tile, public Passive
{
private:
    bool isOpen;
public:
    Door(int row, int col);
    void notify() override;
    std::pair<bool, Tile*> onEnter(Character* who) override;

};

#endif // DOOR_H
