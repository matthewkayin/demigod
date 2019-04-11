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
#include <vector>

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
    void drawRect(int x, int y, int width, int height); //draw an un-filled rectangle
    void drawRect(int x, int y, int width, int height, int thickness); //draw a rectangle with a specified thickness
    void fillRect(int x, int y, int width, int height); //draw a filled rectangle
    //In the rendering functions, sx/sy/sw/sh are the x/y/width/height of the source rectangle for rendering part of the image when it's only partially in frame
    void renderTexture(std::string key, int x, int y); //draw the texture associated with the given key
    void renderPart(std::string key, int index, int x, int y); //draw a sub-image of a texture
    void renderText(std::string text, int x, int y, int size); //draw the string in the font associated with the given key. If x and y are -1, center horizontally or vertically
    void renderConsoleMessage(std::string message, int x, int y);

    int getScreenWidth() const;
    int getScreenHeight() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    bool isFullscreen;

    //Texture and font variables
    const int MESSAGE_SIZE = 16; //font size for console messages
    std::vector<TTF_Font*> fonts;
    std::vector<int> fontSizes;
    int noFonts;
    Texture* textures;
    std::string* textureKeys;
    int noTextures;
};

#endif
