#ifndef CHARACTER_H
#define CHARACTER_H

#include "abstractcontroller.h"
#include <string>

class Tile;

class Character {
private:
    std::string texture;
    Tile* currentTile;
    AbstractController* controller;

public:
    Character(std::string tex, Tile* tile /*, AbstractController* controller*/);
    ~Character();

    std::string getTexture() const;
    Tile* getCurrentTile() const;
    void setCurrentTile(Tile* tile);
    void setController(AbstractController* controller);

    bool moveCharacterTo(Tile* destTile);

    Input move();
};

#endif // CHARACTER_H
