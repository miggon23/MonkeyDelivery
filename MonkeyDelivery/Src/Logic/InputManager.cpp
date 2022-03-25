#include "InputManager.h"
#include "../Logic/Game.h"

InputManager::InputManager(Game *_game)
{
	game = _game;
	/*std::cout << "[DEBUG] frame duration: " << frameDuration() << " ms" << endl;*/
	initSDL();
	IMG_Init(IMG_INIT_PNG);
	game->setRenderer(renderer);
	game->loadTextures();
	joystickDeadZone_ = 8000;

}

InputManager::~InputManager()
{
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
