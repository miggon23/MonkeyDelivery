#pragma once

#include "State.h"
#include "../Buttons/Start.h"

class MenuState : public State {
public:

    MenuState(Game* game);
    ~MenuState();  
    void update() override;
    void draw() override;
    void next() override;
    void registerCommands() override;

    string getStateName() const override {
        return "Menu state";
    };
};