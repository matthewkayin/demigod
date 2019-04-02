//Roguelike Game
//main.cpp

#include "engine.hpp"

void start();

void update();
bool input();
void render();

Engine engine;
bool running = true;

int main(){

    running = engine.init("demigod", 1280, 720);

    start();
    render();

    while(running){

        if(input()){

            update();
            render();
        }
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

void render(){

    engine.setRenderDrawColor(0, 0, 0);
    engine.clear();

    engine.renderTexture("player", 10, 10);

    engine.render();
}
