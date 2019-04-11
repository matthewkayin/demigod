#include "level.hpp"

Level::Level(){

    mapHeight = -1;
    mapWidth = -1;
    map = nullptr;

    generateMap(10, 6);
    //loadMap(dummy2, 33, 16);
    player.setPos(2, 2);
    player.setImage("player");
    messages = new std::string[8];
    head = 0;
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

void Level::enterMessage(std::string message){

    messages[head] = message;
    head++;

    if(head >= NO_MESSAGES){

        head -= NO_MESSAGES;
    }
}

std::string Level::getMessages(int index){

    int indexToUse = index + head;
    if(indexToUse >= NO_MESSAGES){

        indexToUse -= NO_MESSAGES;
    }
    return messages[indexToUse];
}

int Level::getNoMessages(){

    return NO_MESSAGES;
}

void Level::loadMap(const int *prebuilt, const int w, const int h){

    mapWidth = w;
    mapHeight = h;
    map = new int[w * h];

    for(int i = 0; i < w*h; i++){

         map[i] = prebuilt[i];
    }
}

void Level::generateMap(int nocellsw, int nocellsh){

    const int CELL_W = 7;
    const int CELL_H = 7;
    mapWidth = nocellsw * CELL_W;
    mapHeight = nocellsh * CELL_H;
    map = new int[mapWidth * mapHeight];

    for(int i = 0; i < mapWidth; i++){

        for(int j = 0; j < mapHeight; j++){

            int index = (j * mapWidth) + i;
            if(i % CELL_W == 0 || (i + 1) % CELL_W == 0 || j % CELL_H == 0 || (j + 1) % CELL_H == 0){

                map[index] = 0;

            }else{

                map[index] = 1;
            }
        }
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
