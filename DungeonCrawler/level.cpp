#include "level.h"
#include "character.h"
#include "floor.h"
#include "pit.h"
#include "portal.h"
#include "ramp.h"
#include "wall.h"
#include <iostream>
#include <ostream>
//#include <unordered_map>
#include "switch.h"
#include "door.h"

Level::Level(int height, int widht, AbstractController* controller) : height(height), width(widht), tiles(height, std::vector<Tile*>(width, nullptr)), controller(controller) {

    //tiles.resize(height, std::vector<Tile*>(widht, nullptr));   // Initialisiere mit nullptr, wird später überschrieben

}

Level::~Level() {
    std::cout << "LEVEL DESTRUKTOR AUFGERUFEN" << std::endl;
    // Delete tiles
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete tiles[i][j];
        }
    }

    // Delete characters
    for (Character* c : characters) {
        delete c;
    }
}

Level::Level(const Level &other)
{
    std::cout << "KOPIER KONSTRUKTOR AUFGERUFEN" << std::endl;
    copyFrom(other);
}

Level &Level::operator=(const Level &other)
{
    if (this != &other) {
        // Clean up exisiting resources
        // Delete tiles
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete tiles[i][j];
            }
        }
        // Clear Vectors
        portalPositions.clear();
        switches.clear();
        doors.clear();

        // Delete characters
        for (Character* c : characters) {
            delete c;
        }
        characters.clear();

        // Copy data from the other Level, Kopierkonstruktor
        copyFrom(other);
    }
    return *this;
}

void Level::copyFrom(const Level &other)
{
    height = other.height;
    width = other.width;
    controller = other.controller;

    tiles.resize(height);
    for (int i = 0; i < height; ++i) {
        tiles[i].resize(width);
        for (int j = 0; j < width; ++j) {
            Tile* otherTile = other.tiles[i][j];
            Tile* newTile = nullptr;
            if (typeid(*otherTile) == typeid(Floor)) {
                newTile = new Floor(*dynamic_cast<Floor*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Wall)) {
                newTile = new Wall(*dynamic_cast<Wall*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Portal)) {
                newTile = new Portal(*dynamic_cast<Portal*>(otherTile));
                portalPositions.push_back(std::make_pair(i, j));
            } else if (typeid(*otherTile) == typeid(Switch)) {
                newTile = new Switch(*dynamic_cast<Switch*>(otherTile));
                switches.push_back(static_cast<Switch*>(newTile));
            } else if (typeid(*otherTile) == typeid(Door)) {
                newTile = new Door(*dynamic_cast<Door*>(otherTile));
                doors.push_back(static_cast<Door*>(newTile));
            } else if (typeid(*otherTile) == typeid(Ramp)) {
                newTile = new Ramp(*dynamic_cast<Ramp*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Pit)) {
                newTile = new Pit(*dynamic_cast<Pit*>(otherTile));
            }
            tiles[i][j] = newTile;
        }
    }

    characters.resize(other.characters.size());
    for (size_t i = 0; i < characters.size(); ++i) {
        characters[i] = new Character(*other.characters[i]);
        placeCharacter(characters[i], 2, 2);
    }

    // Link portals after copying
    linkPortals(portalPositions);

    // Link switches to doors after copying
    linkSwitches_Doors();

}

int Level::getHeight() const
{
    return height;
}

int Level::getWidth() const
{
    return width;
}

Tile* Level::getTile(int row, int col) {
    if (row >= 0 && row < height && col >= 0 && col < width) {
        return tiles[row][col];
    }
    return nullptr;
}

const Tile* Level::getTile(int row, int col) const {
    if (row >= 0 && row < height && col >= 0 && col < width) {
        return tiles[row][col];
    }
    return nullptr;
}

std::vector<Character *> Level::getCharacters() const
{
    return characters;        // this?
}

void Level::placeCharacter(Character* c, int row, int col) {
    if (row >= 0 && row < height && col >= 0 && col < width) {
        c->setCurrentTile(tiles[row][col]);
        tiles[row][col]->setCharacter(c);
    }
}

void Level::linkPortals(const std::vector<std::pair<int, int> > &portalPositions)
{
    for (size_t i = 0; i < portalPositions.size(); i += 2) {    // Schleife um 2 iterieren, damit wir paare verarbeiten können
        if (i + 1 < portalPositions.size()) {                   // Überprüfen ob es wirklich mehr als 1 portal gibt
            //Portal 1
            int row1 = portalPositions[i].first;
            int col1 = portalPositions[i].second;
            //Portal 2
            int row2 = portalPositions[i + 1].first;
            int col2 = portalPositions[i + 1].second;
            //Portal 1 und 2 verknüpfen
            dynamic_cast<Portal*>(tiles[row1][col1])->setDestination(tiles[row2][col2]);
            dynamic_cast<Portal*>(tiles[row2][col2])->setDestination(tiles[row1][col1]);
        } else {
            std::cerr << "Error: Tile at (" << portalPositions[i].first << ", " << portalPositions[i].second << ") is not a Portal." << std::endl;
        }
    }
}


void Level::linkSwitches_Doors()
{
    for (Switch* s : switches) {
        for (Door* d : doors) {
            if (s && d) {   // Überprüfung auf Nullzeiger
                if (!s->isObserverAttached(d)) {    // Prüfen ob Observer bereits Attached wurde
                    s->attach(d);
                    std::cout << "Attached door to switch\n"; // Debug-Ausgabe
                } else {
                    std::cerr << "Observer already Attached." << std::endl;
                }
            } else {
                std::cerr << "Error: Null switch or door" << std::endl;
            }
        }
    }
}

void Level::generateDefaultLevel()
{
    const std::string_view l = {      // _view speichert nur Zeiger auf die Daten und deren Länge, macht sich keine Kopie
       "##########"
       "#O.......#"
       "#...<....#"
       "#..___...#"
       "#..___...#"
       "#........#"
       "#######X##"
       "#O.......#"
       "#...?....#"
       "##########"

    };

    /*
    std::unordered_map<char, std::pair<int, int>> portalPairs = {   //"eventuelle" eine alternative zu jetztigen portalLinks
        {'A', {-1, -1} },
        {'B', {-1, -1} },
    };*/

    for (int i = 0; i < height; ++i) {
        tiles[i].resize(width);
        for (int j = 0; j < width; ++j) {
            char tileType = l[i * width + j];
            Tile* newTile = nullptr;
            switch (tileType) {
            case '#':
                newTile = new Wall(i, j);
                break;
            case '.':
                newTile = new Floor(i, j);
                break;
            case 'O':
                newTile = new Portal(i, j, nullptr);
                portalPositions.push_back(std::make_pair(i, j));
                break;
            case '?':
                newTile = new Switch(i,j);
                switches.push_back(static_cast<Switch*>(newTile));
                break;
            case 'X':
            case '/':
                newTile = new Door(i,j);
                doors.push_back(static_cast<Door*>(newTile));
                break;
            case '<':
                newTile = new Ramp(i, j);
                break;
            case '_':
                newTile = new Pit(i, j);
                break;
            default:
                // Errors etc
                break;
            }
            tiles[i][j] = newTile;
        }
    }

    Character* hero = new Character("X", tiles[2][2] /*, controller*/);
    characters.push_back(hero);
    placeCharacter(hero, 2, 2);


    // Verknüpfung der Schalter mit den Türen
    linkSwitches_Doors();


    //Portale Aufrufen
    linkPortals(portalPositions);

    // Debugging Hilfe
    std::cout << "Portal Positions:" << std::endl;
    for (size_t i = 0; i < portalPositions.size(); ++i) {
        std::cout << "Row:" << portalPositions[i].first << ", Col: " << portalPositions[i].second << std::endl;
    }

}

