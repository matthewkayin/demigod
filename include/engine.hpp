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
    //Texture class, used to store images that will be rendered on screen
    class Texture{

    public:
        Texture();
        ~Texture();
        bool import(SDL_Renderer* renderer, std::string path); //Import a png file and store it as a texture
        bool import(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color c); //Create a texture from text
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
    bool init(std::string title, int width, int height); //Initializes SDL, returns false if unsuccessful
    bool loadTextures();
    void toggleFullscreen();

    //Rendering functions
    void clear(); //clear the screen of the previous frame
    void render(); //flip everything we've drawn so that it is visible
    void setRenderDrawColor(int r, int g, int b);
    void fillRect(int x, int y, int width, int height); //draw a filled rectangle
    void renderTexture(std::string key, int x, int y); //draw the texture associated with the given key
    void renderText(std::string text, std::string fontKey, int x, int y); //draw the string in the font associated with the given key. If x and y are -1, center horizontally or vertically

    int getScreenWidth() const;
    int getScreenHeight() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    bool isFullscreen;

    //Texture and font variables
    //Different fonts are only for different font heights
    TTF_Font* font_regular;
    TTF_Font* font_menu;
    TTF_Font* font_title;
    Texture* textures;
    std::string* textureKeys;
    int noTextures;
};

#endif
