#include "Button.h"
#include "../Control/States/State.h"
Button::Button(Game* game, int wight, int height, int x, int y) :GameObject(game) {

	setDimension(wight, height);
	setPosition(x, y);

}

Button::Button(Game* game, int x, int y):GameObject(game){
	setDimension(100, 100);
	setPosition(x, y);
}

bool Button::onClick()
{
	SDL_GetMouseState(&x_, &y_);
	SDL_Rect r1 = this->getCollider();
	SDL_Rect mouse = { x_, y_, 20, 20 };

	if (SDL_HasIntersection(&r1, &mouse))
	{
		return true;
	}
	return false;
}

void Button::update(){
}

void Button::ChangeToNewState(State* state){
	game->setSaveState(game->getState());
	game->setState(state);
}

void Button::ChangeToLastState(){
	State* tmp = game->getState();	
	State* saved = game->getSavedState();
	saved->resetInitTime();
	saved->registerCommands();
	game->setState(saved);
	game->removeSavedState();
	delete tmp;
}



