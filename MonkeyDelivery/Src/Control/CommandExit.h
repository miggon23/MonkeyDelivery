#pragma once

#include "Command.h"
#include "../Logic/Game.h"

class CommandExit : public Command {

public:


    CommandExit() {};
    ~CommandExit() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;
};