#pragma once

#include "State.h"

class TestingState : public State {

public:

    TestingState(Game* game, ViewController* v);
    ~TestingState() = default;

    void update() override;
    void draw() override;
    void next() override;
    void registerCommands() override;

    string getStateName() const override {
        return "Testing state";
    };
};

