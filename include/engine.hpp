//Roguelike Game
//engine.hpp
//The engine class provides abstractions for SDL stuff so I don't have to worry
//about it while making the game

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class Engine{

public:
    class Texture{

    public:
        Texture();
        ~Texture();
        bool import(SDL_Renderer* renderer, std::string path);
        bool import(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color c);
        void free();
        SDL_Texture* getImage() const;
        int getWidth() const;
        int getHeight() const;
    private:
        SDL_Texture* image;
        int width;
        int height;
    };

    Engine();
    ~Engine();
    bool init(std::string title, int width, int height);
    bool loadTextures();
    void toggleFullscreen();

    //Rendering functions
    void clear();
    void render();
    void setRenderDrawColor(int r, int g, int b);
    void fillRect(int x, int y, int width, int height);
    void renderTexture(std::string key, int x, int y);
    void renderText(std::string text, std::string fontKey, int x, int y);

    int getScreenWidth() const;
    int getScreenHeight() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    bool isFullscreen;

    TTF_Font* font_regular;
    Texture* textures;
    std::string* textureKeys;
    int noTextures;

    void initializeColorConstants();
};

#endif
