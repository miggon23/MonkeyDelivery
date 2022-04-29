#include "PauseState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../SelectButtonCommand.h"

#include "../UI/Buttons/Options.h"
#include "../UI/Buttons/Menu.h"
#include"../UI/Buttons/Continue.h"

PauseState::PauseState(Game* game) : State(game)
{
	registerCommands();

	addButton(new Continue((int)(game->getWindowWidth() / 2 - buttonW / 2), (int)(game->getWindowHeight() / 2 - buttonH*1.45), buttonW, buttonH, game));
	addButton(new Options((int)(game->getWindowWidth() / 2 - buttonW / 2), (int)(game->getWindowHeight() / 2), buttonW, buttonH, game, 0));
	addButton(new Menu((int)(game->getWindowWidth() / 2 - buttonW / 2), (int)(game->getWindowHeight() / 2 + buttonH*1.45), buttonW, buttonH, game));

	backgroundTexture = game->getTexture(bckg_options);
	selectorTexture = game->getTexture(mission_UI_Selector);
}

void PauseState::update()
{
}

void PauseState::draw()
{
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(),(int)game->getWindowHeight() };
	backgroundTexture->render(rectPanel);
	game->renderText("PAUSED", (int)(game->getWindowWidth() / 2 - 95), (int)(game->getWindowHeight() / 5));

	for (auto b : getButtonsUI()) {
		b->draw();
	}

	rectPanel = { (int)getCurrentButton()->getPosition().getX(), (int)getCurrentButton()->getPosition().getY(), (int)getCurrentButton()->getWidth(), (int)getCurrentButton()->getHeight() };
	selectorTexture->render(rectPanel);
}

void PauseState::next()
{
	/*for (auto b : buttonsUI) {
		delete b;
		b = nullptr;
	}*/
}

void PauseState::moveBox(Vector2D<int> i)
{
	currentSelection += i.getY();
	if (currentSelection < 0) {
		currentSelection = 0;
	}
	else if (currentSelection > buttonsUI.size() - 1) {
		currentSelection = buttonsUI.size() - 1;
	}
}

void PauseState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandClick());
	commandFactory->add(new CommandExit());
	commandFactory->add(new SelectButtonCommand(this));
}
