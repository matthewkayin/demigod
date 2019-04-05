#include "level.hpp"

Level::Level(){

    mapHeight = -1;
    mapWidth = -1;
    map = nullptr;

    loadMap(dummy, 6, 5);
    player.setPos(2, 2);
    player.setImage("player");
}

Level::~Level(){

    delete map;
}

void Level::handleInput(const int inputCode){

    bool invokesPlayerTurn = false;

    switch(inputCode){

        case UP:
            player.incY(-1);
            invokesPlayerTurn = true;
            break;

        case RIGHT:
            player.incX(1);
            invokesPlayerTurn = true;
            break;

        case DOWN:
            player.incY(1);
            invokesPlayerTurn = true;
            break;

        case LEFT:
            player.incX(-1);
            invokesPlayerTurn = true;
            break;

        default:
            std::cout << "Invalid level input code!" << std::endl;
            break;
    }

    if(invokesPlayerTurn){

        //update()
    }
}

void Level::loadMap(const int *prebuilt, const int w, const int h){

    mapWidth = w;
    mapHeight = h;
    map = new int[w * h];

    for(int i = 0; i < w*h; i++){

         map[i] = prebuilt[i];
    }
}

int Level::getTile(int index) const{

    int mapLength = mapWidth * mapHeight;
    if(index >= mapLength){

        std::cout << "Get tile call for index " << index << " is out of range!" << std::endl;
        return -1;
    }

    return map[index];
}

int Level::getTile(int x, int y) const{

    int index = x + (y * mapWidth);
    return getTile(index);
}

int Level::getNoTiles() const{

    return mapWidth * mapHeight;
}

int Level::getMapWidth() const{

    return mapWidth;
}

int Level::getMapHeight() const{

    return mapHeight;
}

Entity Level::getPlayer() const{

    return player;
}
