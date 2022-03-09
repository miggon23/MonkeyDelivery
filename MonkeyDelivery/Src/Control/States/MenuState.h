#pragma once
#include "State.h"

class MenuState : public State {
    //ViewController* vC_;
public:

    MenuState(Game* game,ViewController* view);
    ~MenuState() = default;

    void update() override;
    void draw() override;
    void next() override;
    void registerCommands() override;

    string getStateName() const override {
        return "Menu state";
    };
};