#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "abstractui.h"

class Level;
class AbstractController;

class DungeonCrawler {
private:
    AbstractUI* ui;
    AbstractController* controller;
    Level* currentLevel;
public:
    DungeonCrawler(AbstractUI *ui);
    ~DungeonCrawler();

    void setUI(AbstractUI* ui);
    void setController(AbstractController* controller);

    void drawCurrentLevel();
    Level* getCurrentLevel();

    bool turn();
};

#endif // DUNGEONCRAWLER_H

