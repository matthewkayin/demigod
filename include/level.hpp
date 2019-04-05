//Demigod
//level.hpp
//The level class is where the logic of the main game happens

#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>

class Level{

public:
    Level();
    ~Level();

    void loadMap(const int *prebuilt, const int w, const int h); //loads a non-procedurally generated map

    int getTile(int index) const;
    int getTile(int x, int y) const;
    int getNoTiles() const;
    int getMapWidth() const;
    int getMapHeight() const;
private:
    int *map;
    int mapWidth;
    int mapHeight;

    const int dummy[30] = {1, 1, 1, 1, 1, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 0, 0, 0, 0, 1,
                         1, 1, 1, 1, 1, 1};
};

#endif
