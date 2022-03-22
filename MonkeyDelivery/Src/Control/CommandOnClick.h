#pragma once
#include "Command.h"
#include "../Logic/Game.h"

class SliderClick;
class CommandOnClick: public Command{
    SliderClick* sliderClicked_=nullptr;
public:
    ~CommandOnClick();
    bool parse(SDL_Event & event) override;
    void execute() override;
};

