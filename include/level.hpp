//Demigod
//level.hpp
//The level class is where the logic of the main game happens

#ifndef LEVEL_H
#define LEVEL_H

#include "entity.hpp"
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
    int getNoMessages();

    void loadMap(const int *prebuilt, const int w, const int h); //loads a non-procedurally generated map

    int getTile(int index) const;
    int getTile(int x, int y) const;
    int getNoTiles() const;
    int getMapWidth() const;
    int getMapHeight() const;

    Entity getPlayer() const;
private:
    int *map;
    int mapWidth;
    int mapHeight;

    std::string *messages;
    int head;
    const int NO_MESSAGES = 8;

    Entity player;
    const int dummy[30] = {1, 1, 1, 1, 1, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 1, 1, 1, 1, 1};
};

#endif
