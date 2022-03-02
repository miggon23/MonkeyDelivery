#pragma once
#include "Command.h"
#include "../Logic/Game.h"
#include "../Logic/MissionsPanel.h"

class SelectMissionCommand : public Command {

public:
    SelectMissionCommand(){};

    ~SelectMissionCommand() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;

private:
};

