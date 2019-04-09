#include "level.hpp"

Level::Level(){

    mapHeight = -1;
    mapWidth = -1;
    map = nullptr;

    loadMap(dummy, 6, 5);
    player.setPos(2, 2);
    player.setImage("player");
    messages.init(8);
    messages.push("hello friends it me");
    messages.push("hello friends #it# me");
    messages.push("rest in peace everyone");
    messages.push("asd;flkjasdf;klj");
    messages.push("test test test test test");
    messages.push("I need four more messages to write");
    messages.push("three more messages to go");
    messages.push("two more to do things and stuff");
    messages.push("bro this dude got me like smh");
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

    messages.push(message);
}

std::string Level::getMessages(int index){

    return messages.at(index);
}

int Level::getNoMessages(){

    return messages.size();
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
