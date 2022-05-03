#pragma once

#include "State.h"

class PlayingState : public State {

public:

    PlayingState(Game* game);
    ~PlayingState() = default;

    inline void update() override { game->update(); };
    void draw() override;
    void next() override;
    void registerCommands() override;
    void onEnterState() override;


    string getStateName() const override {
        return "Playing State";
    };
};