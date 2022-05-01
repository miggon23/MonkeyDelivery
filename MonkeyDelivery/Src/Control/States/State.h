#pragma once

#include <string>
#include "../CommandFactory.h"
#include "../ViewController.h"
#include "../../Logic/InputManager.h"
#include "../Button.h"
#include "../UI/Sliders/Slider.h"

class Game;
using namespace std;

class State {

protected:

    Game* game = nullptr;
    CommandFactory* commandFactory = nullptr;
    //unsigned int initTime;
    //unsigned int totalTime;

    bool isFullscreen = false;
    vector<Button*> buttonsUI;
    vector<Slider*> slidersUI;
 
public:
    State(Game* game) : game(game)/*, initTime(SDL_GetTicks()), totalTime(0)*/ {
        commandFactory = new CommandFactory(game);       
    };

    virtual ~State() {
        delete commandFactory;
        for (auto x : buttonsUI) {
            delete x;
            x = nullptr;
        }
        for (auto x:slidersUI){
            delete x;
            x = nullptr;
        }        
    };

    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void next() = 0;
    virtual void jump(State* state);

    virtual Button* getCurrentButton() { return nullptr; };
    virtual void moveBox(Vector2D<int> a) {};

    bool doQuit();
    virtual string getStateName() const = 0;
    void handleEvents();
    virtual void registerCommands() = 0;

    virtual void resetInitTime() {};
    virtual void onExitState() {};
    virtual void onEnterState() {};

    inline vector<Button*> getButtonsUI() { return buttonsUI; };
    inline vector<Slider*> getSlidersUI() { return slidersUI; };
    inline void addButton(Button* button) { buttonsUI.push_back(button); };
    inline void addSlider(Slider* slider) { slidersUI.push_back(slider); };
    vector<SDL_Event>& GetFrameEvents();

};