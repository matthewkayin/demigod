//Roguelike Game
//main.cpp

#include "engine.hpp"

void start();
void keyPressed(int key); //a function to actually do something with inputs once received to make the code a bit cleaner
void update();
void input();
void render();

Engine engine;
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
            if(gamestate == 0){

                gamestate = 1;
            }
            break;

        case B:
            if(gamestate == 0){

                gamestate = 2;
            }
            break;

        case C:
            if(gamestate == 0){

                gamestate = 3;
            }
            break;

        case D:
            if(gamestate == 0){

                running = false;
            }
            break;

        default:
            std::cout << "invalid key sent to keyPressed!" << std::endl;
            break;
    }
}

void update(){


}

void render(){

    engine.setRenderDrawColor(0, 0, 0);
    engine.clear();

    if(gamestate == 0){

        //Render title menu
        engine.setRenderDrawColor(255, 255, 255);
        engine.renderText("DEMIGOD", "title", -1, 50);
        engine.renderText("a. Start", "menu", -1, 350);
        engine.renderText("b. Past Runs", "menu", -1, 400);
        engine.renderText("c. Credits", "menu", -1, 450);
        engine.renderText("d. Exit", "menu", -1, 500);
    }

    if(renderFPS){

        engine.setRenderDrawColor(255, 0, 0);
        engine.renderText("FPS: " + std::to_string(fps), "regular", 5, 5);
    }

    engine.render();
}
