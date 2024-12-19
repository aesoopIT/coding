#ifndef TILE_H
#define TILE_H

#include <string>
#include <utility>

class Character;

class Tile {
private:
    const int row;
    const int col;
    std::string texture;
    Character* character;

protected:
    Tile(std::string texture, int row, int col);

public:
    //static Tile* createTile (const std::string& texture, int row, int col);

    virtual ~Tile();

    bool hasCharacter() const;
    bool moveTo(Tile* destTile, Character* who);
    virtual bool onLeave(Tile* destTile, Character* who);
    virtual std::pair<bool, Tile*> onEnter(Character* who);

    int getRow() const;
    int getCol() const;

    void setCharacter(Character *who);
    void setTexture(const std::string &value);

    void removeCharacter();

    Character* getCharacter() const;
    std::string getTexture() const;

};

#endif // TILE_H
