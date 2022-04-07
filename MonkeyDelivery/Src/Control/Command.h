#pragma once
#include <iostream>
#include<string>
#include "../Logic/Game.h"


class Command
{
protected:
    Game* game;
public:
    Command() {};
    virtual ~Command() = default;
    virtual bool parse(SDL_Event& event) = 0;
    virtual void execute() = 0;
    inline void bind(Game * game) {
        this->game = game;
    }
};