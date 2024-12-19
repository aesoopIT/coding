#include "terminalui.h"
#include "character.h"
#include "tile.h"
#include "wall.h"
#include <iostream>

void TerminalUI::draw(Level* level) {

    if (level == nullptr) {
        std::cerr << "Error: Invalid level object" << std::endl;
        return;
    }

    int height = level->getHeight();
    int width = level->getWidth();
    if (height <= 0 || width <= 0) {
        std::cerr << "Error: Invalid level dimensions" << std::endl;
        return;
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Tile* tile = level->getTile(i, j);
            if (tile != nullptr) {
                    std::cout << tile->getTexture();
            } else {
                std::cerr << "Error: Ivalid tile object" << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

Input TerminalUI::move()
{
    Input input = {0, 0, ""};   // Anfangs initialisierung
    char movement;
    bool validMovement = false;

    std::cout << "Use WSAD to move or Q to exit the game: ";
    while(!validMovement) {
        std::cin >> movement;

        switch (movement) {
        case 'w':
        case 'W':
            input.vertical = -1;
            validMovement = true;
            break;
        case 's':
        case 'S':
            input.vertical = +1;
            validMovement = true;
            break;
        case 'a':
        case 'A':
            input.horizontal = -1;
            validMovement = true;
            break;
        case 'd':
        case 'D':
            input.horizontal = +1;
            validMovement = true;
            break;
        case 'q':
        case 'Q':
            input.command = "exit";
            std::cout << "Exiting the game..." << std::endl;
            validMovement = true;
            break;
        default:
            std::cout << "Invalid input. Use WSAD to move or Q to exit the game." << std::endl;
            break;
        }

        // Flush the input buffer to ignore additional characters
        while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
            std::cin.get();
        }
    }

    return input;
}

void TerminalUI::cannotDoThis(Tile* tile)
{
    if (tile == nullptr) {
        std::cout << "You cannot do this." << std::endl;
        return;
    }

    if (typeid(*tile) == typeid(Wall)) {
        std::cout << "You cannot do this, its a Wall" << std::endl;
    } else {
        std::cout << "You cannot do this, it's an unknown type of Tile." << std::endl;
    }
}
