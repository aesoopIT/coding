#include "dungeoncrawler.h"
#include "terminalui.h"
#include <iostream>
#include <ostream>

using namespace std;

int main()
{
    try {
        AbstractUI* ui = new TerminalUI();
        DungeonCrawler game(ui);

        while (true) {
            if (game.turn()) {
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return 0;
}


// zuweisung operator =, clear einfügen /GEMACHT
// portale, switches und doors die Positionen von normalen Konstruktor aufrufen, keine neue erstellen   (GEMACHT, observer vector anschauen)
