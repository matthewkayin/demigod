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

void Engine::drawRect(int x, int y, int width, int height){

    SDL_Rect rect;
    rect.x = x;
    rect. y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderDrawRect(renderer, &rect);
}

void Engine::drawRect(int x, int y, int width, int height, int thickness){

    //To accomplish the thickness effect, draw a series of one pixel smaller rectangles
    for(int i = 0; i < thickness; i++){

        drawRect(x + i, y + i, width - (i*2), height - (i*2));
    }
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

    //Select a texture based on the given key
    unsigned int i = 0;
    for(i = 0; i < textures.size(); i++){

        if(textureKeys[i] == key){

            toDraw = textures[i]->getImage();
            break;
        }
    }

    //If texture not found, that means we need to load it in for the first time (or it's a typo)
    if(toDraw == nullptr){

        Texture* newTexture = new Texture();
        newTexture->import(renderer, "res/gfx/" + key + ".png");
        textures.push_back(newTexture);
        textureKeys.push_back(key);
        toDraw = newTexture->getImage();
    }

    srcsRect.x = 0;
    srcsRect.y = 0;
    srcsRect.w = 32;
    srcsRect.h = 32;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = srcsRect.w;
    dstRect.h = srcsRect.h;

    SDL_RenderCopy(renderer, toDraw, &srcsRect, &dstRect);
}

void Engine::renderPart(std::string key, int index, int x, int y){

    SDL_Texture* toDraw = nullptr;
    SDL_Rect srcsRect;
    SDL_Rect dstRect;

    unsigned int i = 0;
    for(i = 0; i < textures.size(); i++){

        if(textureKeys[i] == key){

            toDraw = textures[i]->getImage();
            break;
        }
    }

    //If texture not found, that means we need to load it in for the first time (or it's a typo)
    if(toDraw == nullptr){

        Texture* newTexture = new Texture();
        newTexture->import(renderer, "res/gfx/" + key + ".png");
        textures.push_back(newTexture);
        textureKeys.push_back(key);
        toDraw = newTexture->getImage();
    }

    //This function assumes it's being used with a tilemap of 32x32 textures
    //i should be the index of the correct texture regardless of if we find the texture in the for loop or not
    int sx = index % (textures[i]->getWidth() / 32);
    int sy = (index - sx) / (textures[i]->getWidth() / 32);

    srcsRect.x = (sx * 32);
    srcsRect.y = (sy * 32);
    srcsRect.w = 32;
    srcsRect.h = 32;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = srcsRect.w;
    dstRect.h = srcsRect.h;

    SDL_RenderCopy(renderer, toDraw, &srcsRect, &dstRect);
}

void Engine::renderText(std::string text, int x, int y, int size){

    //First we need to create a texture based on the text and given font
    Texture toDraw;
    TTF_Font* fontToUse = nullptr;
    if(fonts.size() != 0){

        //unsigned int in the for loop to prevent warnings when comparing to std::vector.size()
        for(unsigned int i = 0; i < fonts.size(); i++){

            if(fontSizes[i] == size){

                fontToUse = fonts[i];
            }
        }
    }

    //If font vector is empty or if font of given size is not found, create new font and add to vector
    if(fontToUse == nullptr){

        TTF_Font* font = TTF_OpenFont("res/letter_gothic.ttf", size);
        fonts.push_back(font);
        fontSizes.push_back(size);
        fontToUse = font;
    }

    //Set the rendering color equal to the current SDL render color
    SDL_Color c;
    SDL_GetRenderDrawColor(renderer, &c.r, &c.g, &c.b, &c.a);

    //Import the texture
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

void Engine::renderConsoleMessage(std::string message, int x, int y, int fade){

    //Don't run the function if the string is empty (should only happen when console is initially empty)
    if(message == ""){

        return;
    }

    double fadeFactor = 1;
    if(fade == 2){

        fadeFactor = 0.5;

    }else if(fade == 3){

        fadeFactor = 0.3;

    }else if(fade == 4){

        fadeFactor = 0.15;
    }

    //If there are no string rendering commands
    if(message.find("#") == std::string::npos){

        setRenderDrawColor(255*fadeFactor, 255*fadeFactor, 255*fadeFactor);
        renderText(message, x, y, MESSAGE_SIZE);

    }else{

        std::string white = "";
        std::string red = "";

        bool colorIsWhite = true;
        //unsigned int to avoid warning when comparing with message.length()
        for(unsigned int i = 0; i < message.length(); i++){

            if(message[i] == '#'){

                colorIsWhite = !colorIsWhite;

            }else{

                if(colorIsWhite){

                    white = white + message[i];
                    red = red + " ";

                }else{

                    white = white + " ";
                    red = red + message[i];
                }
            }
        }

        setRenderDrawColor(255*fadeFactor, 255*fadeFactor, 255*fadeFactor);
        renderText(white, x, y, MESSAGE_SIZE);
        setRenderDrawColor(255*fadeFactor, 0, 0);
        renderText(red, x, y, MESSAGE_SIZE);
    }
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
