#include "CommandExit.h"

bool CommandExit::parse(SDL_Event& event) {
    if (event.type == SDL_QUIT)
        return true;
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key = event.key.keysym.sym;
        if (key == SDLK_p)
            return true;
    }
    return false;
}

void CommandExit::execute() {
    game->setUserExit();
}