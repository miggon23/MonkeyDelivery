#pragma once

#include "State.h"

class PlayingState : public State {

public:

    PlayingState(Game* game);
    ~PlayingState() = default;

    void update() override;
    void draw() override;
    void next() override;
    void registerCommands() override;

    string getStateName() const override {
        return "Playing State";
    };
};
