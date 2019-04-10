#include "level.hpp"

Level::Level(){

    mapHeight = -1;
    mapWidth = -1;
    map = nullptr;

    loadMap(dummy, 6, 5);
    player.setPos(2, 2);
    player.setImage("player");
    messages = new std::string[8];
    head = 0;
    enterMessage("hmm hum delete me");
    enterMessage("I have to go to a meeting with the President at #8:30# tomorrow");
    enterMessage("Yeah, it's confirmed #3:30#");
    enterMessage("Okay wow yeah that's great");
    enterMessage("Welp let's just drink so oat milk I guess");
    enterMessage("Capitalism is in everything even those things with a good cause");
    enterMessage("Is that a bad thing? Is it possible for an example of capitalism to be not bad?");
    enterMessage("something something #communism#");
    enterMessage("vote bernie 2020");
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
