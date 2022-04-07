#pragma once
#include "Command.h"

class NextStateCommand : public Command {

public:
    NextStateCommand() {
    };
    ~NextStateCommand() = default;

    bool parse(SDL_Event& event) override;
    void execute() override;
};