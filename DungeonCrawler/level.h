#ifndef LEVEL_H
#define LEVEL_H

#include "abstractcontroller.h"
#include "door.h"
#include "switch.h"
#include <vector>

class Tile;
class Character;

class Level {
private:
    int height;
    int width;
    std::vector<std::vector<Tile*>> tiles;
    std::vector<Character*> characters;
    AbstractController* controller;

    std::vector<std::pair<int, int>> portalPositions;
    std::vector<Switch*> switches;
    std::vector<Door*> doors;

    void linkPortals(const std::vector<std::pair<int, int>>& portalPositions);

    void copyFrom(const Level& other);  // muss noch verbessert werden

    void linkSwitches_Doors();

public:
    Level(int height, int widht, AbstractController* controller);
    Level(const Level& other);  // copy Konstruktor
    Level& operator=(const Level& other);
    ~Level();

    int getHeight() const;
    int getWidth() const;

    Tile* getTile(int row, int col);
    const Tile* getTile(int row, int col) const;

    std::vector<Character*> getCharacters() const;
    void placeCharacter(Character* c, int row, int col);

    void generateDefaultLevel();

};

#endif // LEVEL_H
