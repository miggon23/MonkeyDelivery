#include "ViewController.h"
#include "../Logic/Game.h"

#include "States/MenuState.h"
#include "States/PlayingState.h"


ViewController::ViewController(Game* _game) {
    game = _game;
    std::cout << "[DEBUG] frame duration: " << frameDuration() << " ms" << endl;
    initSDL();
    IMG_Init(IMG_INIT_PNG);
    game->setRenderer(renderer);
    game->loadTextures();
    
    game->setState(new MenuState(game));

    timer_ = Timer::Instance();
}

void ViewController::run() {
    
    while (!game->getState()->doQuit()) {
        timer_->Update();

        handleEvents();

        if (timer_->DeltaTime() >= 1.0f / FRAME_RATE) {

            timer_->Reset();
            clearBackground();
            game->getState()->update();
            game->getState()->draw();
            SDL_RenderPresent(renderer);
        }
    }
}

void ViewController::clearBackground() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


vector<SDL_Event>& ViewController::GetFrameEvents()
{
    static vector<SDL_Event> frame_events;
    return frame_events;
}

void ViewController::handleEvents() {
    game->getState()->handleEvents();
}

uint32_t ViewController::frameDuration() {
    return 1000 / FRAME_RATE;
}

void ViewController::initSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(game->getGameName().c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game->getWindowWidth(),
        game->getWindowHeight(),
        SDL_WINDOW_SHOWN);
    setWindow(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    

    if (window == nullptr || renderer == nullptr)
        throw string("Error creating SDL window or renderer");

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, &screenSurface->clip_rect, 0xFF);
    SDL_UpdateWindowSurface(window);
}

ViewController::~ViewController() {
    timer_->Release();
    timer_ = nullptr;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
