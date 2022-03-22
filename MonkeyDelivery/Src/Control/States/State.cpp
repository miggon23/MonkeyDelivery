#include "State.h"
#include "../../Logic/Game.h"


bool State::doQuit() {
    bool quit = game->isUserExit();
    if (quit)
    {
        delete this;
    }
    return quit;
}

void State::handleEvents() {
    SDL_Event event;
    // Método simple de eventos
    while (SDL_PollEvent(&event)) {
        Command* command = commandFactory->getCommand(event);
        if (command != nullptr) {
            command->execute();
            break;
        }

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