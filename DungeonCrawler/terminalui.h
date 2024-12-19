#ifndef TERMINALUI_H
#define TERMINALUI_H
#include "abstractui.h"
#include<abstractcontroller.h>
//#include<abstractview.h>

class TerminalUI :  public AbstractUI , public AbstractController{
public:
    void draw(Level* level) override;
    Input move() override;

    void cannotDoThis(Tile* tile) override;
};

#endif // TERMINALUI_H
