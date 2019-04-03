#include "engine.hpp"

Engine::Engine(){

    window = nullptr;
    renderer = nullptr;
    isFullscreen = false;
}

Engine::~Engine(){

    SDL_ShowCursor(SDL_ENABLE);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Engine::init(std::string title, int width, int height){

    if(window || renderer){

        std::cout << "Engine has already been initialized!" << std::endl;
        return false;
    }

    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        std::cout << "Unable to initialize SDL!" << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); //or use SDL_RENDERER_ACCELERATED for hardware rendering

    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags)){

        std::cout << "Unable to initialize SDL_image! SDL Error: " << IMG_GetError() << std::endl;
        return false;
    }

    if(TTF_Init() == -1){

        std::cout << "Unable to initialize SDL_ttf! SDL Error: " << TTF_GetError() << std::endl;
        return false;
    }

    if(!window || !renderer){

        std::cout << "Unable to initialize engine!" << std::endl;
        return false;
    }

    if(!loadTextures()){

        return false;
    }

    font_regular = TTF_OpenFont("res/helvetica.ttf", 18);
    font_title = TTF_OpenFont("res/helvetica.ttf", 90);
    font_menu = TTF_OpenFont("res/helvetica.ttf", 30);

    return true;
}

bool Engine::loadTextures(){

    noTextures = 1;
    textures = new Texture[noTextures];
    textureKeys = new std::string[noTextures];

    if(!textures[0].import(renderer, "res/gfx/player.png")){

        return false;
    }
    textureKeys[0] = "player";

    return true;
}

void Engine::toggleFullscreen(){

    if(isFullscreen){

        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    }else{

        SDL_SetWindowFullscreen(window, 0);
    }

    isFullscreen = !isFullscreen;
}

int Engine::getScreenWidth() const{

    return SCREEN_WIDTH;
}

int Engine::getScreenHeight() const{

    return SCREEN_HEIGHT;
}

void Engine::clear(){

    SDL_RenderClear(renderer);
}

void Engine::render(){

    SDL_RenderPresent(renderer);
}

void Engine::setRenderDrawColor(int r, int g, int b){

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void Engine::fillRect(int x, int y, int width, int height){

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderFillRect(renderer, &rect);
}

void Engine::renderTexture(std::string key, int x, int y){

    //srcsRect is the portion of the image to take from
    //dstRect is what to draw on the screen
    //So srcs rect could be used to take all of or part of an image
    //And dst rect could be used to position where we draw the image and how much we ought to scale it by
    SDL_Texture* toDraw = nullptr;
    SDL_Rect srcsRect;
    SDL_Rect dstRect;

    //Select a texture based on the given key, they're stored in parallel arrays
    for(int i = 0; i < noTextures; i++){

        if(textureKeys[i] == key){

            toDraw = textures[i].getImage();
            srcsRect.x = 0;
            srcsRect.y = 0;
            srcsRect.w = textures[i].getWidth();
            srcsRect.h = textures[i].getHeight();
            dstRect.x = x;
            dstRect.y = y;
            dstRect.w = srcsRect.w;
            dstRect.h = srcsRect.h;
        }
    }

    if(toDraw == nullptr){

        std::cout << "Failed to fetch texture! " << std::endl;
    }

    SDL_RenderCopy(renderer, toDraw, &srcsRect, &dstRect);
}

void Engine::renderText(std::string text, std::string fontKey, int x, int y){

    //First we need to create a texture based on the text and given font
    Texture toDraw;
    TTF_Font* fontToUse = nullptr;
    if(fontKey == "regular"){

        fontToUse = font_regular;

    }else if(fontKey == "title"){

        fontToUse = font_title;

    }else if(fontKey == "menu"){

        fontToUse = font_menu;
    }
    SDL_Color c;
    SDL_GetRenderDrawColor(renderer, &c.r, &c.g, &c.b, &c.a);
    toDraw.import(renderer, text, fontToUse, c);

    //If x or y are -1, center the text horizontally or vertically
    int theX = x;
    int theY = y;
    if(theX == -1){

        theX = (SCREEN_WIDTH / 2) - (toDraw.getWidth() / 2);
    }
    if(theY == -1){

        theY = (SCREEN_HEIGHT / 2) - (toDraw.getHeight() / 2);
    }

    //Now we can do the actual rendering
    SDL_Rect srcsRect = SDL_Rect{0, 0, toDraw.getWidth(), toDraw.getHeight()};
    SDL_Rect dstRect = SDL_Rect{theX, theY, toDraw.getWidth(), toDraw.getHeight()};
    SDL_RenderCopy(renderer, toDraw.getImage(), &srcsRect, &dstRect);
}

Engine::Texture::Texture(){

    image = nullptr;
    width = 0;
    height = 0;
}

Engine::Texture::~Texture(){

    free();
}

bool Engine::Texture::import(SDL_Renderer* renderer, std::string path){

    free();
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr){

        std::cout << "Unable to load image! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if(newTexture == nullptr){

        std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    width = loadedSurface->w;
    height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    image = newTexture;
    return image != nullptr;
}

bool Engine::Texture::import(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color c){

    free();
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* textSurface = nullptr;

    textSurface = TTF_RenderText_Solid(font, text.c_str(), c);

    if(textSurface == nullptr){

        std::cout << "Unable to render text to surface! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    width = textSurface->w;
    height = textSurface->h;

    newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if(newTexture == nullptr){

        std::cout << "Unable to create texture! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_FreeSurface(textSurface);

    image = newTexture;
    return image != nullptr;
}

void Engine::Texture::free(){

    if(image != nullptr){

        width = 0;
        height = 0;
        SDL_DestroyTexture(image);
        image = nullptr;
    }
}

SDL_Texture* Engine::Texture::getImage() const{

    return image;
}

int Engine::Texture::getWidth() const{

    return width;
}

int Engine::Texture::getHeight() const{

    return height;
}
