#pragma once
#include "Command.h"
#include "../Logic/Game.h"
#include "./States/ShopState.h"

class ShopCommand : public Command
{
public:
    ShopCommand(ShopState* state) : shopState_(state) {};
    

    ~ShopCommand() = default;
    bool parse(SDL_Event & event) override;
    void execute() override;

private:
   
    ShopState* shopState_;
    int moveCursor_;
    bool buy_ = false;
};

