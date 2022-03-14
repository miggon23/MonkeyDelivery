#pragma once

#include "Command.h"
#include "../Logic/Game.h"

class CommandClick : public Command {

public:


    //CommandExit() {};
    ~CommandClick() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;
};