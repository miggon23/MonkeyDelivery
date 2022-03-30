#include "InputManager.h"
#include "../Logic/Game.h"
#include "../Control/States/MenuState.h"
#include "../Control/States/PlayingState.h"
#include "../Control/States/PauseState.h"
#include "../sdlutils/InputHandler.h"


InputManager::InputManager(Game* _game)
{
	game = _game;
	std::cout << "[DEBUG] frame duration: " << frameDuration() << " ms" << endl;
	//initSDL();
	IMG_Init(IMG_INIT_PNG);
	renderer = game->getRenderer();
	game->loadTextures();
	game->initBrightness();
	//commandFactory = new CommandFactory(game);
	joystickDeadZone_ = 8000;
	game->setState(new MenuState(game));
	timer_ = Timer::Instance();

}

InputManager::~InputManager()
{
	timer_->Release();
	timer_ = nullptr;
	SDL_JoystickClose(gamepad_);
	gamepad_ = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}

void InputManager::run()
{
	//auto& ihdlr = ih();
	while (!game->getState()->doQuit()) {
		timer_->Update();

		handleEvents();
//		ihdlr.refresh();

		if (timer_->DeltaTime() >= 1.0f / FRAME_RATE) {
			timer_->Reset();
			clearBackground();
			game->getState()->update();
			game->getState()->draw();
			SDL_RenderPresent(renderer);
		}

	}
}

void InputManager::initSDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//comprobacion joystick
	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No joysticks connected!\n");
	}
	else
	{
		//asociar joystick
		gamepad_ = SDL_JoystickOpen(0);
		if (gamepad_ == NULL)
		{
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			printf("Name: %s\n", SDL_JoystickNameForIndex(0));
		}
	}


	window = SDL_CreateWindow(game->getGameName().c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		game->getWindowWidth(),
		game->getWindowHeight(),
		SDL_WINDOW_SHOWN);


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		printf("Window or renderer could not be created! SDL Error: %s\n", SDL_GetError());

	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, &screenSurface->clip_rect, 0xFF);
	SDL_UpdateWindowSurface(window);

}

void InputManager::handleEvents()
{
	auto state = game->getState();
	game->getState()->handleEvents();
	//SDL_Event event;
	// /*Método simple de eventos*/
	//while (SDL_PollEvent(&event)) {
		/*if(state==MenuState)*/
		/*Command* command = commandFactory->getCommand(event);
		if (command != nullptr) {
			command->execute();
			break;
		}
		if (event.type == SDL_JOYAXISMOTION) {
			printf("axis: %i %i\n", event.jaxis.axis, event.jaxis.value);
		}
		else if (event.type == SDL_JOYBUTTONDOWN) {
			printf("button: %i\n", event.jbutton.button);
		}*/

	/*}*/

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
	return 1000 / FRAME_RATE_;
}
