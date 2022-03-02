#pragma once

#include "SDL.h"
#include "CommandFactory.h"
#include <string>



const int FRAME_RATE = 30;

class Game;
class ViewController {
private:
    Game* game;
    SDL_Window* window = nullptr;
    
    SDL_Renderer* renderer = nullptr;
    CommandFactory* commandFactory;

    void initSDL();
public:
    ViewController(Game* game);

    ~ViewController();

    void run();
    void handleEvents();
    void clearBackground();

    vector<SDL_Event>& GetFrameEvents(); //Vector de eventos, registra mas de 1 por frame

    unsigned int frameDuration();
};



