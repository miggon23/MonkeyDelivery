#pragma once

#include "SDL.h"
#include "CommandFactory.h"
#include <string>
#include "../utils/Timer.h"


class Game;
class ViewController {
private:
    Game* game;
    SDL_Window* window = nullptr;
    
    SDL_Renderer* renderer = nullptr;
    CommandFactory* commandFactory;
    SDL_Event event;
    Timer* timer_;

    void initSDL();
public:
    ViewController(Game* game);

    ~ViewController();

    void run();
    void handleEvents();
    void clearBackground();
    SDL_Window* getWindow(){ return window; }
    void setWindow(SDL_Window* w) { window = w; }
    vector<SDL_Event>& GetFrameEvents(); //Vector de eventos, registra mas de 1 por frame

    unsigned int frameDuration();
};