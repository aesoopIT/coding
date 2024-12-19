#include "character.h"
#include "tile.h"

Character::Character(std::string tex, Tile* tile /*, AbstractController *controller*/) : texture(tex),
    currentTile(tile), controller(nullptr) {
}

Character::~Character() {}

std::string Character::getTexture() const {
    return texture;
}

Tile* Character::getCurrentTile() const {
    return currentTile;
}

void Character::setCurrentTile(Tile* tile) {
    currentTile = tile;
}

void Character::setController(AbstractController*controller)
{
    //delete this->ui;
    this->controller = controller;
}

bool Character::moveCharacterTo(Tile* destTile) {
    if (destTile->hasCharacter()) {
        return false;
    }
    return currentTile->moveTo(destTile, this);
}

Input Character::move()
{
    if (controller != nullptr) {
        return controller->move();
    }
    return Input();
}
