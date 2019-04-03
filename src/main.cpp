//Roguelike Game
//main.cpp

#include "engine.hpp"

void start();

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
bool f11Lock = false;
bool f2Lock = false;

int main(){

    running = engine.init("demigod", 1280, 720);

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

            switch(e.key.keysym.sym){

                case SDLK_F11:
                    if(!f11Lock){

                        engine.toggleFullscreen();
                        f11Lock = true;
                    }
                    break;

                case SDLK_F2:
                    if(!f2Lock){

                        renderFPS = !renderFPS; //toggle the variable
                        f2Lock = true;
                    }
            }

        }else if(e.type == SDL_KEYUP){

            switch(e.key.keysym.sym){

                case SDLK_F11:
                    if(f11Lock){

                        f11Lock = false;
                    }
                    break;

                case SDLK_F2:
                    if(f2Lock){

                        f2Lock = false;
                    }
                    break;
            }
        }
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
