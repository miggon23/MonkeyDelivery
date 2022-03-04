#pragma once
#include "Command.h"
#include "../Logic/Game.h"
#include "../Logic/MissionsPanel.h"
#include "../Control/States/MissionSelectionState.h"

class SelectMissionCommand : public Command {

public:
    SelectMissionCommand() : missionSelection_(nullptr), moveCursor_(0) {};
    SelectMissionCommand(MissionSelectionState* ms) : missionSelection_(ms), moveCursor_(0) { };

    ~SelectMissionCommand() = default;
    bool parse(SDL_Event& event) override;
    void execute() override;

private:
    int moveCursor_;
    MissionSelectionState* missionSelection_;
};

