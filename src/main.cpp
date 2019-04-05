//Roguelike Game
//main.cpp

#include "engine.hpp"
#include "level.hpp"

void start();

void keyPressed(int key); //a function to actually do something with inputs once received to make the code a bit cleaner
void input();

void update();

void render();
void renderLevel();
void renderEntity(Entity e);

Engine engine;
Level level;
bool running = true;
const unsigned int TARGET_FPS = 60;
const unsigned int SECOND = 1000;
const unsigned int FRAME_TIME = SECOND / TARGET_FPS;
int fps = 0;
int gamestate = 0;
bool renderFPS = true;

//key locks so that events only happen once per keypress
const int noKeys = 6;
bool keyLock[noKeys];
const SDL_Keycode keyCode[noKeys] = {SDLK_F11, SDLK_F2, SDLK_a, SDLK_b, SDLK_c, SDLK_d};
const int F11 = 0;
const int F2 = 1;
const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;

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
        update();
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

        default:
            std::cout << "Invalid key sent to keyPressed!" << std::endl;
            break;
    }
}

void update(){


}

void render(){

    engine.setRenderDrawColor(0, 0, 0);
    engine.clear();

    if(gamestate == MENU_TITLE){

        //Render title menu
        engine.setRenderDrawColor(255, 255, 255);
        engine.renderText("DEMIGOD", "title", -1, 50);
        engine.renderText("a. Start", "menu", -1, 350);
        engine.renderText("b. Past Runs", "menu", -1, 400);
        engine.renderText("c. Credits", "menu", -1, 450);
        engine.renderText("d. Exit", "menu", -1, 500);

    }else if(gamestate == GAME){

        renderLevel();
        renderEntity(level.getPlayer());
    }

    if(renderFPS){

        engine.setRenderDrawColor(255, 0, 0);
        engine.renderText("FPS: " + std::to_string(fps), "regular", 5, 5);
    }

    engine.render();
}

void renderLevel(){

    for(int i = 0; i < level.getMapWidth(); i++){

        for(int j = 0; j < level.getMapHeight(); j++){

            engine.renderPart("tileset", level.getTile(i, j), i * 32, j * 32);
        }
    }
}

void renderEntity(Entity e){

    engine.renderTexture(e.getImage(), e.getX() * 32, e.getY() * 32);
}
