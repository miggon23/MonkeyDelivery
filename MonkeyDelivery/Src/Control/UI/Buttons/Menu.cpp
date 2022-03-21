#include "Menu.h"
#include "../../../Logic/Game.h"
#include "../../States/MenuState.h"

Menu::Menu(int x, int y, int w, int h, Game* game) :Button(game, w, h, x, y)
{
	setTexture(backButtonTexture);
}

void Menu::onCursorCollision()
{
	game->setState(new MenuState(game));
}
