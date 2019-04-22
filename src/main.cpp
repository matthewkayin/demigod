//Roguelike Game
//main.cpp

#include "engine.hpp"
#include "level.hpp"
#include "globals.hpp"

void initGame();

//Input functions
void keyPressed(int key);
void input();

//Rendering functions
void render();
void renderLevel();
void renderEntity(Entity e);
void renderGameUI();

enum Gamestate{

    MENU_TITLE,
    MENU_CHAR_CREATE,
    MENU_CHAR_HISTORY,
    MENU_CREDITS,
    GAME
};

//Engine variables
Engine engine;
Level level;
bool running = true;
const unsigned int TARGET_FPS = 60;
const unsigned int SECOND = 1000;
const unsigned int FRAME_TIME = SECOND / TARGET_FPS;
int fps = 0;
Gamestate gamestate = MENU_TITLE;
bool renderFPS = true;

//key locks so that events only happen once per keypress
//The keylock and keycode arrays are parallel, for example keyLock[0] is the lock for keyCode[0], which is F11
const int noKeys = 10;
bool keyLock[noKeys];
const SDL_Keycode keyCode[noKeys] = {SDLK_F11, SDLK_F2, SDLK_a, SDLK_b, SDLK_c, SDLK_d,
                                    SDLK_UP, SDLK_RIGHT, SDLK_DOWN, SDLK_LEFT};
//Each key in this enum is an index to the keylock keycode array, using these makes the code more readable
enum Keys{

    F11 = 0,
    F2 = 1,
    A = 2,
    B = 3,
    C = 4,
    D = 5,
    UP = 6,
    RIGHT = 7,
    DOWN = 8,
    LEFT = 9
};

int main(){

    //running is set equal to engine.init() because if init fails running will be false
    running = engine.init("demigod", 1280, 720);

    //initialize all the keyLocks to false
    for(int i = 0; i < noKeys; i++){

        keyLock[i] = false;
    }

    initGame();

    //variables for game loop timing
    unsigned int lastSec = SDL_GetTicks();
    unsigned int lastTime = lastSec;
    unsigned int currentTime;
    int frames = 0;

    //game loop
    while(running){

        //main game loop
        input();
        render();
        frames++;

        currentTime = SDL_GetTicks();

        //If at least a second has passed, record how many frames occured during that second
        if(currentTime - lastSec >= SECOND){

            fps = frames;
            frames = 0;
            lastSec += SECOND;
        }

        //If the time in this frame was less than the frame time, sleep for the remaining availiable time
        //This sleeping ensures that the game doesn't try to take up more cpu time than it needs
        if(currentTime - lastTime < FRAME_TIME){

            unsigned int delayTime = FRAME_TIME - (currentTime - lastTime);
            SDL_Delay(delayTime);
        }

        lastTime = SDL_GetTicks();
    }

    return 0;
}

//Initializes all game objects and variables
void initGame(){

    //setup the game here
}

//Gets SDL key input and sends it to the keyPressed function
void input(){

    SDL_Event e;
    //This while loop handles each event, each iteration is an SDL event
    while(SDL_PollEvent(&e) != 0){

        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){

            //close the game
            running = false;
        }

        if(e.type == SDL_KEYDOWN){

            SDL_Keycode key = e.key.keysym.sym; //get which key
            //Loop through all of our the game-specific keyCodes
            for(int i = 0; i < noKeys; i++){

                //If the key is one of the game-specific keycodes, then we should handle the keypress
                if(keyCode[i] == key){

                    //If the keyLock is off that means this event is the initial keypress
                    if(!keyLock[i]){

                        keyPressed(i); //handle the key in keyPressed()
                        keyLock[i] = true; //set the keylock to true so that keyPressed can't be called again until the key is released
                    }

                    //we've handled the key, so there's no need to iterate through the rest of them
                    break;
                }
            }

        }else if(e.type == SDL_KEYUP){

            SDL_Keycode key = e.key.keysym.sym; //get which key
            //Loop through all of our game-specific keyCodes
            for(int i = 0; i < noKeys; i++){

                //If the key is one of the game-specific keycodes, then we should handle the keypress
                if(keyCode[i] == key){

                    //If the keyLock is on that means the key was pressed and has now been released
                    if(keyLock[i]){

                        keyLock[i] = false; //disable the keylock so the key can be pressed again
                    }

                    //we've handled the key, so there's no need ot iterate through the rest of them
                    break;
                }
            }
        }
    }
}

//This function handles the part of a keyPress that actually affect the game
void keyPressed(int key){

    switch(key){

        case F11:
            engine.toggleFullscreen();
            break;

        case F2:
            renderFPS = !renderFPS;
            break;

        case A:
            if(gamestate == MENU_TITLE){

                //gamestate = MENU_CHAR_CREATE;
                gamestate = GAME;
            }
            break;

        case B:
            if(gamestate == MENU_TITLE){

                gamestate = MENU_CHAR_HISTORY;
            }
            break;

        case C:
            if(gamestate == MENU_TITLE){

                gamestate = MENU_CREDITS;
            }
            break;

        case D:
            if(gamestate == MENU_TITLE){

                running = false;
            }
            break;

        case UP:
            if(gamestate == GAME){

                level.handleInput(level.UP);
            }
            break;

        case RIGHT:
            if(gamestate == GAME){

                level.handleInput(level.RIGHT);
            }
            break;

        case DOWN:
            if(gamestate == GAME){

                level.handleInput(level.DOWN);
            }
            break;

        case LEFT:
            if(gamestate == GAME){

                level.handleInput(level.LEFT);
            }
            break;

        default:
            std::cout << "Invalid key sent to keyPressed!" << std::endl;
            break;
    }
}

void render(){

    //fill the screen with black
    engine.setRenderDrawColor(0, 0, 0);
    engine.clear();

    if(gamestate == MENU_TITLE){

        //Render title menu
        engine.setRenderDrawColor(255, 255, 255);
        engine.renderText("DEMIGOD", -1, 50, 90);
        engine.renderText("a. Start", -1, 350, 30);
        engine.renderText("b. Past Runs", -1, 400, 30);
        engine.renderText("c. Credits", -1, 450, 30);
        engine.renderText("d. Exit", -1, 500, 30);

    }else if(gamestate == GAME){

        renderLevel();
        renderEntity(level.getEnemy());
        renderEntity(level.getPlayer());
        renderGameUI();
    }

    if(renderFPS){

        engine.setRenderDrawColor(255, 0, 0);
        engine.renderText("FPS: " + std::to_string(fps), 5, 5, 18);
    }

    //flips everything we just drew up above from the buffer onto the actual screen
    engine.render();
}

void renderLevel(){

    for(int i = 0; i < level.getMapWidth(); i++){

        for(int j = 0; j < level.getMapHeight(); j++){

            int tileX = (i - level.getOffsetX()) * 32;
            int tileY = (j - level.getOffsetY()) * 32;

            //If tile is out of bounds, continue to next tile
            if(tileX < 0 || tileX >= CANVAS_W || tileY < 0 || tileY >= CANVAS_H){

                continue;
            }

            engine.renderPart("tileset", level.getTile(i, j), CANVAS_X + tileX, CANVAS_Y + tileY);
        }
    }
}

void renderEntity(Entity e){

    int entityX = (e.getX() - level.getOffsetX()) * 32;
    int entityY = (e.getY() - level.getOffsetY()) * 32;

    //If tile is out of bounds, exit function
    if(entityX < 0 || entityX >= CANVAS_W || entityY < 0 || entityY >= CANVAS_H){

        return;
    }

    engine.renderTexture(e.getImage(), CANVAS_X + entityX, CANVAS_Y + entityY);
}

void renderGameUI(){

    engine.setRenderDrawColor(255, 255, 255);
    engine.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, FRAME_THICKNESS); //draw main game frame
    engine.drawRect(FRAME_X, FRAME_Y + FRAME_H + FRAME_THICKNESS + 32, FRAME_W, 140,  FRAME_THICKNESS); //draw console frame
    engine.renderText("Player", FRAME_X + FRAME_THICKNESS, FRAME_Y + FRAME_H + FRAME_THICKNESS + 5, 25); //draw player name

    //draw player stats
    engine.renderText("Health " + std::to_string(level.getPlayer().getHealth()), FRAME_X + FRAME_THICKNESS + FRAME_W, 20, 16);

    //draw console box messages
    for(int i = 0; i < level.getNoMessages(); i++){

        engine.renderConsoleMessage(level.getMessages(i), FRAME_X + FRAME_THICKNESS + 5, FRAME_Y + FRAME_H + FRAME_THICKNESS + 40 + (i * 16), level.getMessageFade(i));
    }
}
