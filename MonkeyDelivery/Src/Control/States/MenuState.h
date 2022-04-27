#pragma once

#include "State.h"
#include "../UI/Buttons/Start.h"

class MenuState : public State {
    Texture* backgroundTexture;
    Texture* titleTexture;
    const double buttonW = 300, buttonH = 140;
    const int titleW = 700, titleH = 258;
public:

    MenuState(Game* game); 
    ~MenuState() { backgroundTexture = nullptr; };
    void update() override;
    void draw() override;
    void next() override;
    void registerCommands() override;
    void onEnterState() override;

    string getStateName() const override {
        return "Menu state";
    };
};