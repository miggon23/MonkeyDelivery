#include "State.h"
#include "../../Logic/Game.h"
#include "../../sdlutils/InputHandler.h"


bool State::doQuit() {
    bool quit = game->isUserExit();
    if (quit)
    {
        delete this;
    }
    return quit;
}

void State::handleEvents() {
    auto& ihdlr = ih();
    SDL_Event event;
    // Método simple de eventos
    while (SDL_PollEvent(&event)) {
        Command* command = commandFactory->getCommand(event);
        if (command != nullptr) {
            command->execute();
            ihdlr.update(event);
            break;
        }
        ihdlr.update(event);

    }
}

vector<SDL_Event>& State::GetFrameEvents()
{
    static vector<SDL_Event> frame_events;
    return frame_events;
}

void State::jump(State* state) {
    game->setState(state);
    delete this;
}