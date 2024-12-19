#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H

#include "level.h"

class AbstractUI {
public:
    virtual ~AbstractUI() = default;

    virtual void draw(Level* level) = 0;

    virtual void cannotDoThis(Tile* tile) = 0;
};

#endif // ABSTRACTUI_H
