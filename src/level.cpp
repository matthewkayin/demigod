#include "level.hpp"

Level::Level(){

    srand(time(NULL));

    mapHeight = -1;
    mapWidth = -1;
    map = nullptr;

    generateMap(10, 6);
    //loadMap(dummy2, 33, 16);
    player.setPos(2, 2);
    player.setImage("player");
    player.setHealth(20);
    enemy.setPos(10, 2);
    enemy.setImage("enemy");
    enemy.setHealth(10);
    messages = new std::string[8];
    messageFades = new int[8];
    head = 0;

    for(int i = 0; i < NO_MESSAGES; i++){

        messageFades[i] = -1;
    }
}

Level::~Level(){

    delete map;
}

void Level::handleInput(const int inputCode){

    bool invokesPlayerTurn = false;
    int lastMove = -1;

    switch(inputCode){

        case UP:
            player.incY(-1);
            invokesPlayerTurn = true;
            lastMove = 1;
            break;

        case RIGHT:
            player.incX(1);
            invokesPlayerTurn = true;
            lastMove = 2;
            break;

        case DOWN:
            player.incY(1);
            invokesPlayerTurn = true;
            lastMove = 3;
            break;

        case LEFT:
            player.incX(-1);
            invokesPlayerTurn = true;
            lastMove = 4;
            break;

        default:
            std::cout << "Invalid level input code!" << std::endl;
            break;
    }

    if(invokesPlayerTurn){

        update(lastMove);
    }
}

void Level::enterMessage(std::string message){

    messages[head] = message;
    messageFades[head] = 0;
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

int Level::getMessageFade(int index){

    int indexToUse = index + head;
    if(indexToUse >= NO_MESSAGES){

        indexToUse -= NO_MESSAGES;
    }
    return messageFades[indexToUse];
}

int Level::getNoMessages(){

    return NO_MESSAGES;
}

void Level::update(int lastMove){

    //Update console message fade levels
    bool emptyMessages = false;
    for(int i = 0; i < NO_MESSAGES; i++){

        if(messageFades[i] == 0){

            messageFades[i] = 1;

        }else if(messageFades[i] == 1){

            messageFades[i] = 2;

        }else if(messageFades[i] == -1){

            emptyMessages = true;
        }
    }
    if(!emptyMessages){

        messageFades[head] = 4;
        messageFades[head + 1] = 3;
    }

    //If player move resulted in a collision, prevent the move from happening and have the player interact with the object
    if(player.getCollision(enemy) && enemy.getHealth() > 0){

        switch(lastMove){

            case 1:
                player.incY(1);
                break;

            case 2:
                player.incX(-1);
                break;

            case 3:
                player.incY(-1);
                break;

            case 4:
                player.incX(1);
                break;
        }

        int damage = rand() % 5 + 1;
        enemy.takeDamage(damage);
        enterMessage("You punched the demon, dealing #" + std::to_string(damage) + "# damage");

        lastMove = -1;
    }

    //Update map offset based on player movement

    if(lastMove == 4 && offsetx != 0 && player.getX() - offsetx < CANVAS_TILE_W * 0.25){

        offsetx--;

    }else if(lastMove == 2 && offsetx != mapWidth - CANVAS_TILE_W && player.getX() - offsetx > CANVAS_TILE_W * 0.75){

        offsetx++;

    }else if(lastMove == 1 && offsety != 0 && player.getY() - offsety < CANVAS_TILE_H * 0.25){

        offsety--;

    }else if(lastMove == 3 && offsety != mapHeight - CANVAS_TILE_H && player.getY() - offsety > CANVAS_TILE_H * 0.75){

        offsety++;
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

int Level::getOffsetX() const{

    return offsetx;
}

int Level::getOffsetY() const{

    return offsety;
}

Entity Level::getPlayer() const{

    return player;
}

Entity Level::getEnemy() const{

    return enemy;
}
