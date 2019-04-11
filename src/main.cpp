//Roguelike Game
//main.cpp

#include "engine.hpp"
#include "level.hpp"

void start();

void keyPressed(int key); //a function to actually do something with inputs once received to make the code a bit cleaner
void input();

void render();
void renderLevel();
void renderEntity(Entity e);
void renderGameUI();

Engine engine;
Level level;
bool running = true;
const unsigned int TARGET_FPS = 60;
const unsigned int SECOND = 1000;
const unsigned int FRAME_TIME = SECOND / TARGET_FPS;
int fps = 0;
int gamestate = 0;
bool renderFPS = true;

//variables for when we're rendering only onto specific frames of the UI
//The frame variables are for the UI functions use, the main frame vars are for the rendering functions use (texture/entity rendering etc.)
const int FRAME_X = 20;
const int FRAME_Y = 15;
const int FRAME_W = 1028;
const int FRAME_H = 516;
const int FRAME_THICKNESS = 4;
const int MAIN_FRAME_X = FRAME_X + FRAME_THICKNESS;
const int MAIN_FRAME_Y = FRAME_Y + FRAME_THICKNESS;
const int MAIN_FRAME_W = FRAME_W - FRAME_THICKNESS;
const int MAIN_FRAME_H = FRAME_H - FRAME_THICKNESS;

//key locks so that events only happen once per keypress
const int noKeys = 10;
bool keyLock[noKeys];
const SDL_Keycode keyCode[noKeys] = {SDLK_F11, SDLK_F2, SDLK_a, SDLK_b, SDLK_c, SDLK_d,
                                    SDLK_UP, SDLK_RIGHT, SDLK_DOWN, SDLK_LEFT};
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

//game state enumeration for cleaner code
const int MENU_TITLE = 0;
const int MENU_CHAR_CREATE = 1;
const int MENU_CHAR_HISTORY = 2;
const int MENU_CREDITS = 3;
const int GAME = 4;

int main(){

    running = engine.init("demigod", 1280, 720);

    for(int i = 0; i < noKeys; i++){

        keyLock[i] = false;
    }

    start();

    unsigned int lastSec = SDL_GetTicks();
    unsigned int lastTime = lastSec;
    unsigned int currentTime;
    int frames = 0;

    //game loop
    while(running){

        input();
        render();
        frames++;

        currentTime = SDL_GetTicks();
        if(currentTime - lastSec >= SECOND){

            //If at least a second has passed, record how many frames occured during that second
            fps = frames;
            frames = 0;
            lastSec += SECOND;
        }
        if(currentTime - lastTime < FRAME_TIME){

            //If there's time left over, delay until it's time to render the next frame
            unsigned int delayTime = FRAME_TIME - (currentTime - lastTime);
            SDL_Delay(delayTime);
        }

        lastTime = SDL_GetTicks();
    }

    return 0;
}

void start(){

    //setup the game here
}

void input(){

    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){

        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){

            running = false;
        }

        if(e.type == SDL_KEYDOWN){

            SDL_Keycode key = e.key.keysym.sym;
            for(int i = 0; i < noKeys; i++){

                if(keyCode[i] == key){

                    if(!keyLock[i]){

                        keyPressed(i);
                        keyLock[i] = true;
                    }

                    break;
                }
            }

        }else if(e.type == SDL_KEYUP){

            SDL_Keycode key = e.key.keysym.sym;
            for(int i = 0; i < noKeys; i++){

                if(keyCode[i] == key){

                    if(keyLock[i]){

                        keyLock[i] = false;
                    }

                    break;
                }
            }
        }
    }
}

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
        renderEntity(level.getPlayer());
        renderGameUI();
    }

    if(renderFPS){

        engine.setRenderDrawColor(255, 0, 0);
        engine.renderText("FPS: " + std::to_string(fps), 5, 5, 18);
    }

    engine.render();
}

void renderLevel(){

    for(int i = 0; i < level.getMapWidth(); i++){

        for(int j = 0; j < level.getMapHeight(); j++){

            int tileX = i * 32;
            int tileY = j * 32;

            //Check if the tile is out of bounds
            if(tileX < 0 || tileX >= MAIN_FRAME_W || tileY < 0 || tileY >= MAIN_FRAME_H){

                continue; //tile is out of bounds, so don't render and just go to the next tile
            }

            engine.renderPart("tileset", level.getTile(i, j), MAIN_FRAME_X + tileX, MAIN_FRAME_Y + tileY);
        }
    }
}

void renderEntity(Entity e){

    int entityX = e.getX() * 32;
    int entityY = e.getY() * 32;

    if(entityX < 0 || entityX >= MAIN_FRAME_W || entityY < 0 || entityY >= MAIN_FRAME_H){

        return;
    }

    engine.renderTexture(e.getImage(), MAIN_FRAME_X + (e.getX() * 32), MAIN_FRAME_Y + (e.getY() * 32));
}

void renderGameUI(){

    engine.setRenderDrawColor(255, 255, 255);
    engine.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, FRAME_THICKNESS);
    engine.drawRect(FRAME_X, FRAME_Y + FRAME_H + FRAME_THICKNESS + 32, FRAME_W, 140,  FRAME_THICKNESS);
    engine.renderText("Player", FRAME_X + FRAME_THICKNESS, FRAME_Y + FRAME_H + FRAME_THICKNESS + 5, 25);
    for(int i = 0; i < level.getNoMessages(); i++){

        engine.renderConsoleMessage(level.getMessages(i), 26, 568 + (i * 16));
    }
}
