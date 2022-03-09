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
        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_f) {
                if (!isFullscreen) {
                    isFullscreen = !isFullscreen;
                    int err = SDL_SetWindowFullscreen(vC_->getWindow(), SDL_WINDOW_FULLSCREEN);
                    if (err) {
                        const char* e = SDL_GetError();
                        std::cout << e << std::endl;
                    }
                }
                else {
                    isFullscreen = !isFullscreen;
                    int err = SDL_SetWindowFullscreen(vC_->getWindow(), SDL_WINDOW_SHOWN);
                    if (err) {
                        const char* e = SDL_GetError();
                        std::cout << e << std::endl;
                    }
                }
                
            }
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