#include "MenuState.h"
#include "../../Logic/Game.h"

//#include "../../utils/Music.h"

#include "../NextStateCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../States/PlayingState.h"
#include "../UI/Buttons/Exit.h"
#include "../UI/Buttons/Start.h"
#include "../UI/Buttons/Options.h"
#include "../UI/Buttons/Credits.h"
#include "../UI/Buttons/ExitButton.h"

MenuState::MenuState(Game* game) : State(game) {
	game->clearSavedState();
	registerCommands();
	addButton(new Start(game->getWindowWidth() / 2 - buttonW / 2, game->getWindowHeight() / 2 - buttonH * 1.3, buttonW, buttonH, game));
	addButton(new Options(game->getWindowWidth() / 2 - buttonW / 2, game->getWindowHeight() / 2, buttonW, buttonH, game, 1));
	addButton(new Credits(game->getWindowWidth() / 2 - buttonW / 2, game->getWindowHeight() / 2 + buttonH * 1.3, buttonW, buttonH, game));
	addButton(new ExitButton(game->getWindowWidth() / 2 - buttonW / 2, game->getWindowHeight() / 2 + buttonH * 2.6, buttonW, buttonH, game));

	backgroundTexture = game->getTexture(bckg_Image);
	titleTexture = game->getTexture(bckg_GameTitle);
	game->clearSavedState();	
	
}

void MenuState::registerCommands()
{
	commandFactory->add(new CommandClick());
	commandFactory->add(new CommandExit());
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
	SDL_Rect rectPanel = { 0,0,game->getWindowWidth(),game->getWindowHeight() };
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
}

void MenuState::next() {
	cout << "Next State " << endl;
	game->setState(new PlayingState(game));
	delete this;
}