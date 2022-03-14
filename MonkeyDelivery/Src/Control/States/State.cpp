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

    //// Método de múltiples eventos
    //while (SDL_PollEvent(&event) != 0)
    //{
    //    GetFrameEvents().push_back(event);
    //}
    //for (auto e : GetFrameEvents()) //Ejecutamos los executes de los comandos de los eventos registrados
    //{
    //    vector<Command*> commands = commandFactory->getCommand(e);
    //    for (auto i : commands)
    //    {
    //        if (i != nullptr) {
    //            i->execute();
    //        }
    //    }
    //}

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