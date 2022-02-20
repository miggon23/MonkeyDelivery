#include "MenuState.h"
#include "../../Logic/Game.h"

#include "../NextStateCommand.h"
#include "../CommandExit.h"

#include "../States/PlayingState.h"

MenuState::MenuState(Game* game) : State(game)
{
    registerCommands();
}

void MenuState::registerCommands()
{
    commandFactory->add(new NextStateCommand());
    commandFactory->add(new CommandExit());
}

void MenuState::update()
{
}

void MenuState::draw()
{
    int x = game->getWindowWidth() / 2 - 250;
    int y = game->getWindowHeight() / 2 - 50;

    vector<string> texts = {
            "Welcome to Monkey Delivery",
            "Press SPACE to start"
    };

    game->renderText(texts, x, y, 75, 75);
}

void MenuState::next()
{
    cout << "Next State " << endl;
    game->setState(new PlayingState(game));
    delete this;
}


