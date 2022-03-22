#pragma once

#include "Command.h"
#include "../Logic/Game.h"
class SliderClick;
class CommandClick : public Command {
    SliderClick* sliderClicked_ = nullptr;
public:
    ~CommandClick();
    bool parse(SDL_Event& event) override;
    void execute() override;
};