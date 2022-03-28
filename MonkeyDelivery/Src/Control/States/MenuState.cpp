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

MenuState::MenuState(Game* game) : State(game) {
	registerCommands();
	addButton(new Start(game->getWindowWidth() / 2 - 200, game->getWindowHeight() - 700, 400, 180, game));
	addButton(new Options(game->getWindowWidth() / 2 - 200, game->getWindowHeight() - 500, 400, 180, game, 1));
	addButton(new Credits(game->getWindowWidth() / 2 - 200, game->getWindowHeight() - 300, 400, 180, game));

	backgroundTexture = game->getTexture(backgroundTex);
	/* Music* m = new Music("../Sounds/menumusic.wav");
	 m->play(-1);*/ //-1 son infinitos loops
}

void MenuState::registerCommands()
{
	commandFactory->add(new CommandClick());
	commandFactory->add(new CommandExit());
}

void MenuState::update() {

}

void MenuState::draw()
{
	SDL_Rect rectPanel = { 0,0,game->getWindowWidth(),game->getWindowHeight() };
	backgroundTexture->render(rectPanel);

	int x = game->getWindowWidth() / 2 - 250;
	int y = game->getWindowHeight() / 2 - 350;

	vector<string> texts = {
			"Welcome to Monkey Delivery"
	};

	game->renderText(texts, x, y, 75, 75);
	for (auto b : getButtonsUI()) {
		b->draw();
	}


	//game->DrawBrightness();
}

void MenuState::next() {
	cout << "Next State " << endl;
	game->setState(new PlayingState(game));
	delete this;
}
