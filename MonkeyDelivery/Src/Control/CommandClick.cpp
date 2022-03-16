#include "CommandClick.h"
#include "Button.h"
#include "../Control/States/State.h"
bool CommandClick::parse(SDL_Event& event) {
   if (event.type == SDL_MOUSEBUTTONDOWN)
        return true;
   
    return false;
}

void CommandClick::execute() {
    for (auto it : game->getState()->getButtonsUI()) {
        if (it->onClick()) {
            it->onCursorCollision();
            break;
        }
    }
}