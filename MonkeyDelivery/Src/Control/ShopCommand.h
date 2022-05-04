#pragma once
#include "Command.h"
#include "../Logic/Game.h"
#include "./States/ShopState.h"

class ShopCommand : public Command
{
public:
    ShopCommand(ShopState* state) : shopState_(state),moveCursor_(-1),interaccion_(-1) {};
    

    ~ShopCommand() = default;
    bool parse(SDL_Event & event) override;
    void execute() override;

private:
   
    ShopState* shopState_;
    int moveCursor_;
    int interaccion_;// -1=Comprar //0= mov Horizontal  //1= mov Vertical
};

