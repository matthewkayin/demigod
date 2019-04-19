//Demigod
//level.hpp
//The level class is where the logic of the main game happens

#ifndef LEVEL_H
#define LEVEL_H

#include "entity.hpp"
#include "globals.hpp"
#include <iostream>
#include <string>

class Level{

public:

    Level();
    ~Level();

    //Input functions and constants
    enum Inputs{

        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3
    };
    void handleInput(const int inputCode);
    void enterMessage(std::string message);
    std::string getMessages(int index);
    int getMessageFade(int index);
    int getNoMessages();

    void update(int lastMove);

    void loadMap(const int *prebuilt, const int w, const int h); //loads a non-procedurally generated map
    void generateMap(int nocellsw, int nocellsh);

    int getTile(int index) const;
    int getTile(int x, int y) const;
    int getNoTiles() const;
    int getMapWidth() const;
    int getMapHeight() const;

    int getOffsetX() const;
    int getOffsetY() const;

    Entity getPlayer() const;
    Entity getEnemy() const;
private:
    int *map;
    int mapWidth;
    int mapHeight;

    std::string *messages;
    int *messageFades;
    int head;
    const int NO_MESSAGES = 8;

    int offsetx = 0;
    int offsety = 0;

    Entity player;
    Entity enemy;
    const int dummy[30] = {1, 1, 1, 1, 1, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 1, 1, 1, 1, 1};
};

#endif
