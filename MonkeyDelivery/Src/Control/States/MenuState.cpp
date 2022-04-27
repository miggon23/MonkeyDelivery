#include "MenuState.h"
#include "../../Logic/Game.h"

//#include "../../utils/Music.h"

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

	selectorX = game->getWindowWidth() / 2 - buttonW / 2;
	selectorY = game->getWindowHeight() / 2 - buttonH;

	backgroundTexture = game->getTexture(bckg_Image);
	titleTexture = game->getTexture(bckg_GameTitle);
	selectorTexture = game->getTexture(mission_UI_Selector);
	game->clearSavedState();	
	
}

void MenuState::registerCommands()
{
	commandFactory->add(new CommandClick());
	commandFactory->add(new CommandExit());
	commandFactory->add(new SelectButtonCommand(this));
}

void MenuState::onEnterState()
{
	sdlutils().musics().at("menumusic").play(-1);
}

void MenuState::update() {
	sdlutils().musics().at("menumusic").setMusicVolume(game->getMusicVolume()*game->getGeneralVolume());
}

void MenuState::draw()
{
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(),(int)game->getWindowHeight() };
	backgroundTexture->render(rectPanel);
	rectPanel = { (int)game->getWindowWidth() / 2 - titleW / 2, titleH / 3, titleW, titleH };
	titleTexture->render(rectPanel);

	/*int x = game->getWindowWidth() / 2 - 250;
	int y = game->getWindowHeight() / 2 - 350;

	vector<string> texts = {
			"Welcome to Monkey Delivery"
	};

	game->renderText(texts, x, y, 75, 75);*/
	//game->DrawBrightness();
	for (auto b : getButtonsUI()) {
		b->draw();
	}

	// Dibujar selector
	rectPanel = {selectorX, selectorY, selectorW, selectorH};
	selectorTexture->render(rectPanel);
}

void MenuState::next() {
	cout << "Next State " << endl;
	game->setState(new PlayingState(game));
	delete this;
}

void MenuState::moveBox(int i) {
	if (i == -1 && currentSelection != 0) {
		selectorY -= selectorInc;
		currentSelection--;
	}
	else if (i == 1 && currentSelection != buttonsUI.size() - 1) {
		selectorY += selectorInc;
		currentSelection++;
	}
}