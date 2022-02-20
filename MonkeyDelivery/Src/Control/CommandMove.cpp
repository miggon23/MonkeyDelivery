#include "CommandMove.h"

bool CommandMove::parse(SDL_Event& event)
{
	
	if (event.type == SDL_KEYDOWN) {
		SDL_Keycode key = event.key.keysym.sym;
		//Derecha
		if (key == SDLK_d) {
			dir = 1;
			return true;
		}
		//Izquierda
		else if (key == SDLK_a) {
			dir = -1;
			return true;
		}
		//Arriba
		if (key == SDLK_w) {
			dirV = -1;
			return true;
		}
		//Abajo
		else if (key == SDLK_s) {
			dirV = 1;
			return true;
		}
	}
	//Reseteos
	if (event.type == SDL_KEYUP) {
		SDL_Keycode key = event.key.keysym.sym;
		//Movimiento Horizontal
		if (key == SDLK_d || key == SDLK_a) {
			dir = 0;
			return true;
		}
		//Movimiento Vertical
		else if(key == SDLK_w|| key == SDLK_s){
			dirV = 0;
			return true;
		}
	}
	return false;
}

void CommandMove::execute()
{
	game->move(pair<double, double>(dir, dirV)); //Movimiento del player
}
