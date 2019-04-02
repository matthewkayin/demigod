//Roguelike Game
//main.cpp

#include "engine.hpp"

void start();

void update();
bool input();
void render();

Engine engine;
bool running = true;
const unsigned int TARGET_FPS = 60;
const unsigned int SECOND = 1000;
const unsigned int FRAME_TIME = SECOND / TARGET_FPS;
int fps = 0;

int main(){

    running = engine.init("demigod", 1280, 720);

    start();

    unsigned int lastSec = SDL_GetTicks();
    unsigned int lastTime = lastSec;
    unsigned int currentTime;
    int frames = 0;

    while(running){

        input();
        update();
        render();
        frames++;

        currentTime = SDL_GetTicks();
        if(currentTime - lastSec >= SECOND){

            fps = frames;
            frames = 0;
            std::cout << "FPS = " << fps << std::endl;
            lastSec += SECOND;
        }
        if(currentTime - lastTime < FRAME_TIME){

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

bool input(){

    bool keyPressed = false;

    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){

        if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){

            running = false;
        }

        if(e.type == SDL_KEYDOWN){

            keyPressed = true;
        }
    }

    return keyPressed;
}

void update(){


}
int playerX = 10;
void render(){

    engine.setRenderDrawColor(0, 0, 0);
    engine.clear();

    engine.renderTexture("player", playerX, 10);
    playerX += 2;
    engine.renderText("You have died.", "regular", 100, 100);

    engine.render();
}
