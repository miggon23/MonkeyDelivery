#pragma once
#include "State.h"

class MenuState : public State {

public:

    MenuState(Game* game);
    ~MenuState() = default;

    void update() override;
    void draw() override;
    void next() override;
    void registerCommands() override;

    string getStateName() const override {
        return "Menu state";
    };
};