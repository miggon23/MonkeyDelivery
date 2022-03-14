#include "CommandClick.h"
bool CommandClick::parse(SDL_Event& event) {
   if (event.type == SDL_MOUSEBUTTONDOWN)
        return true;
   
    return false;
}

void CommandClick::execute() {
    
}