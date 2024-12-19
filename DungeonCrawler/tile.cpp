#include "tile.h"
#include "character.h"
#include "portal.h"
#include "string"

int Tile::getRow() const
{
    return row;
}

int Tile::getCol() const
{
    return col;
}

void Tile::setCharacter(Character *who)
{
    this->character = who;
}

void Tile::setTexture(const std::string &value)
{
    texture = value;
}

void Tile::removeCharacter()
{
    this->character = nullptr;
}

Tile::Tile(std::string texture, int row, int col) : row(row), col(col), texture(texture), character(nullptr) {}

/*Tile *Tile::createTile(const std::string &texture, int row, int col)
{
    return new Tile(texture, row ,col);
}*/

Tile::~Tile() {}

std::string Tile::getTexture() const {
    if (character) {
        return character->getTexture();
    } else {
        return texture;
    }
}

bool Tile::hasCharacter() const {
    return (character != nullptr);
}

Character *Tile::getCharacter() const
{
    return character;
}

bool Tile::moveTo(Tile* destTile, Character* who) {

    if (!onLeave(destTile, who)) {
        return false;   // Kachel darf nicht verlassen werden
    }

    if (destTile->onEnter(who).first) {
        character = nullptr;
        destTile->character = who;
        who->setCurrentTile(destTile);
        return true;
    }
    return false;
}

bool Tile::onLeave(Tile* destTile, Character* who) {
    return true;
}

std::pair<bool, Tile *> Tile::onEnter(Character *who)
{
    return std::make_pair(true, nullptr);
}

