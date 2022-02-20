#include "MenuState.h"
#include "../../Logic/Game.h"

MenuState::MenuState(Game* game) : State(game)
{

}

void MenuState::update()
{
}

void MenuState::draw()
{
    int x = game->getWindowWidth() / 2 - 100;
    int y = game->getWindowHeight() / 2 - 50;

    vector<string> texts = {
            "Welcome to Monkey Delivery"
    };

    game->renderText(texts, x, y, 0, 10);
}

void MenuState::next()
{
    cout << "Next State " << endl;
    //game->setState(new Level_0_State(game));
    delete this;
}

void MenuState::registerCommands()
{
	//commandFactory->add(new NextStateCommand());
}
