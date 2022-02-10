#pragma once

#include "SDL.h"

#include <string>



const int FRAME_RATE = 30;

class Game;
class ViewController {
private:
    Game* game;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    void initSDL();
public:
    ViewController(Game* game);

    ~ViewController();

    void run();
    void handleEvents();
    void clearBackground();

    unsigned int frameDuration();
};



