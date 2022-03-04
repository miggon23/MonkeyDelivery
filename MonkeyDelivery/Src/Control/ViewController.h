#pragma once

#include "SDL.h"
#include "CommandFactory.h"
#include <string>
#include "../Utils/Timer.h"



const int FRAME_RATE = 120;

class Game;
class ViewController {
private:
    Game* game;
    SDL_Window* window = nullptr;
    
    SDL_Renderer* renderer = nullptr;
    CommandFactory* commandFactory;

    Timer* timer_;

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



