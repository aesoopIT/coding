#include "dungeoncrawler.h"
#include "character.h"
#include "portal.h"
#include "wall.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

DungeonCrawler::DungeonCrawler(AbstractUI* ui) : ui(ui) {

    /*
    currentLevel = new Level(10, 10, controller);
    currentLevel->generateDefaultLevel();
    */

    setUI(ui);

    ///*
    Level* tmp = new Level(10, 10, nullptr); // Initialisiere Level mit Größe und Controller-Pointer
    tmp->generateDefaultLevel(); // Generiere das Level

    currentLevel = new Level(*tmp); // Nutze Kopierkonstruktor
    delete tmp;
    std::cout << "Delete tmp aufgerufen." << std::endl;

    // Test assignment operator
    tmp = new Level(10, 10, nullptr); // Initialisiere neues Level
    tmp->generateDefaultLevel(); // Generiere das Level
    *currentLevel = *tmp; // Nutze Zuweisungsoperator
    delete tmp;
    //*/
}

DungeonCrawler::~DungeonCrawler() {
    delete currentLevel;
    delete ui;
}

void DungeonCrawler::setUI(AbstractUI* ui)
{
    // delete this->ui;
    this->ui = ui;

    controller = dynamic_cast<AbstractController*>(ui);
    if (!controller) {
        // Error: UI ist kein AbstractController
        throw std::runtime_error("Failed to cast ui to AbstractController");
    }

}

void DungeonCrawler::setController(AbstractController *controller)
{
    this->controller = controller;
}

Level *DungeonCrawler::getCurrentLevel()
{
    return currentLevel;
}

bool DungeonCrawler::turn() {
    ui->draw(currentLevel);

    for (Character* c : currentLevel->getCharacters()) {
        Input move = controller->move();

        if (move.command == "exit") {
            return true;
        }

        int newRow = c->getCurrentTile()->getRow() + move.vertical;   // Vertikale Bewegung entspricht der Zeilenbewegung
        int newCol = c->getCurrentTile()->getCol() + move.horizontal; // Horizontale Bewegung entspricht der Spaltenbewegung

        Tile* newTile = currentLevel->getTile(newRow, newCol);

        if (newTile) {
            if (typeid(*newTile) == typeid(Wall)) {
                ui->cannotDoThis(newTile);  //Übergibt das Tile objekt für Identifizierung
            } else if (typeid(*newTile) == typeid(Portal)) {
                Portal* portal = dynamic_cast<Portal*>(newTile);
                Tile* destination = portal->getDestination();
                //c->moveCharacterTo(portal);
                c->moveCharacterTo(destination);
            } else {
                c->moveCharacterTo(newTile);
            }
        }
    }
    //system("cls");
    return false;
}
