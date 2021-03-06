#include "MenuState.h"
#include "../../Logic/Game.h"

#include "../NextStateCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../SelectButtonCommand.h"
#include "../States/PlayingState.h"
#include "../UI/Buttons/Exit.h"
#include "../UI/Buttons/Start.h"
#include "../UI/Buttons/Options.h"
#include "../UI/Buttons/Credits.h"
#include "../UI/Buttons/ExitButton.h"

MenuState::MenuState(Game* game) : State(game) {
	game->clearSavedState();
	registerCommands();
	addButton(new Start((int)(game->getWindowWidth() / 2 - buttonW / 2), (int)(game->getWindowHeight() / 2 - buttonH), buttonW, buttonH, game));
	addButton(new Options((int)(game->getWindowWidth() / 2 - buttonW / 2), (int)(game->getWindowHeight() / 2), buttonW, buttonH, game, 1));
	addButton(new Credits((int)(game->getWindowWidth() / 2 - buttonW / 2), (int)(game->getWindowHeight() / 2 + buttonH), buttonW, buttonH, game));
	addButton(new ExitButton((int)(game->getWindowWidth() / 2 - buttonW / 2), (int)(game->getWindowHeight() / 2 + buttonH*2), buttonW, buttonH, game));

	backgroundTexture = game->getTexture(bckg_Image);
	titleTexture = game->getTexture(bckg_GameTitle);
	selectorTexture = game->getTexture(button_Selector);
	game->clearSavedState();
	sdlutils().musics().at("menumusic").play(-1);
}

void MenuState::registerCommands()
{
	commandFactory->add(new CommandClick());
	commandFactory->add(new CommandExit());
	commandFactory->add(new SelectButtonCommand(this));
}


void MenuState::update() {
	sdlutils().musics().at("menumusic").setMusicVolume((int)(game->getMusicVolume()*game->getGeneralVolume()));
}

void MenuState::draw()
{
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(),(int)game->getWindowHeight() };
	backgroundTexture->render(rectPanel);
	rectPanel = { (int)game->getWindowWidth() / 2 - titleW / 2, titleH / 6, titleW, titleH };
	titleTexture->render(rectPanel);

	for (auto b : getButtonsUI()) {
		b->draw();
	}

	// Dibujar selector
	rectPanel = { (int)getCurrentButton()->getPosition().getX(), (int)getCurrentButton()->getPosition().getY(), (int)getCurrentButton()->getWidth(), (int)getCurrentButton()->getHeight() };
	selectorTexture->render(rectPanel);
}

void MenuState::next() {
	cout << "Next State " << endl;
	game->setState(new PlayingState(game));
	delete this;
}

void MenuState::moveBox(Vector2D<int> i) {
	
	currentSelection += i.getY();
	if (currentSelection < 0) {
		currentSelection = 0;
	}
	else if (currentSelection > buttonsUI.size() - 1) {
		currentSelection = (int)buttonsUI.size()- 1;
	}
}