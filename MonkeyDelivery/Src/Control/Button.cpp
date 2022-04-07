#include "Button.h"
#include "../Control/States/State.h"

Button::Button(Game* game, int wight, int height, int x, int y) :GameObject(game), y_(0), x_(0) {

	setDimension(wight, height);
	setPosition(x, y);

}

Button::Button(Game* game, int x, int y):GameObject(game), y_(0), x_(0) {
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

void Button::ChangeToNewState(State* state,bool guardar){
	State* TMP = game->getState();
	game->ClearState();
	game->setState(state);
	if (guardar) {
		game->setSaveState(TMP);
	}
	else{
		delete TMP;
		TMP = nullptr;
	}
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

void Button::ChangeToOptionsState(){
	State* TMP = game->getState();
	game->ClearState();	
	game->setSaveState(TMP);
	game->setState(game->getOptionsState());
}

void Button::ChangeToLastaStateNO_DELETE_LAST(){
	State* saved = game->getSavedState();
	saved->resetInitTime();
	saved->registerCommands();
	game->setState(saved);
	game->removeSavedState();
}