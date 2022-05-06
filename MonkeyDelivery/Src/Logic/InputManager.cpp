#include "InputManager.h"
#include "../Logic/Game.h"
#include "../Control/States/MenuState.h"
#include "../Control/States/PlayingState.h"
#include "../Control/States/OptionsState.h"
#include "../Control/States/GameOverState.h"
#include "../sdlutils/InputHandler.h"


InputManager::InputManager(Game* _game)
{
	game = _game;
	std::cout << "[DEBUG] frame duration: " << frameDuration() << " ms" << endl;
	IMG_Init(IMG_INIT_PNG);
	renderer = game->getRenderer();
	game->loadTextures();
	game->setState(new GameOverState(game));
	/*game->setState(new MenuState(game));
	game->initOptionsState();*/
	timer_ = Timer::Instance();
}

InputManager::~InputManager()
{
	timer_->Release();
	timer_ = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}

void InputManager::run()
{
	while (!game->getState()->doQuit()) {
		auto state = game->getState();
		timer_->Update(state->getStateName());
		state->handleEvents();

		if (timer_->DeltaTime() >= 1.0f / FRAME_RATE) {
			clearBackground();
			game->getState()->update();
			game->getState()->draw();
			SDL_RenderPresent(renderer);
			timer_->Reset();
		}
	}
}

vector<SDL_Event>& InputManager::GetFrameEvents()
{
	static vector<SDL_Event> frame_events;
	return frame_events;
}

void InputManager::clearBackground()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

unsigned int InputManager::frameDuration()
{
	return 1000 / FRAME_RATE;
}
