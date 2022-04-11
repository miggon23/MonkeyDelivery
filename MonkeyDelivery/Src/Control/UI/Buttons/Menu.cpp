#include "Menu.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"
#include "../../States/PlayingState.h"

Menu::Menu(int x, int y, int w, int h, Game* game) :Button(game, w, h, x, y)
{
	setTexture(button_Continue);
}

void Menu::onCursorCollision()
{
	
	game->clearSavedState();
	ChangeToNewState(new MenuState(game),false);
}