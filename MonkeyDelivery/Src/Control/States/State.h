#pragma once

#include <string>
#include "../CommandFactory.h"
#include "../ViewController.h"

class Game;
using namespace std;

class State {

protected:
    Game* game = nullptr;
    CommandFactory* commandFactory = nullptr;
    ViewController* vC_;
   // Uint32 initTime;
    unsigned int initTime;
   // Uint32 totalTime;
    unsigned int totalTime;

    bool isFullscreen = false;
public:
    State(Game* game,ViewController* v) : game(game) {
        commandFactory = new CommandFactory(game);
        vC_ = v;
        
    };

    virtual ~State() {
        delete commandFactory;
    };

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void next() = 0;
    virtual void jump(State* state);
    bool doQuit();
    virtual string getStateName() const = 0;
    void handleEvents();
    virtual void registerCommands() = 0;

    virtual void resetInitTime() {};

    vector<SDL_Event>& GetFrameEvents();
};