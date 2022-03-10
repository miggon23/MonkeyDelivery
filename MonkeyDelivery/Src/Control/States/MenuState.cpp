#include "MenuState.h"
#include "../../Logic/Game.h"

#include "../NextStateCommand.h"
#include "../CommandExit.h"

#include "../States/PlayingState.h"
#include "../Buttons/Exit.h"
#include "../Buttons/Start.h"
#include "../Buttons/Options.h"


MenuState::MenuState(Game* game, ViewController* view) : State(game,view){
    registerCommands();
    buttons.push_back(new Start(game->getWindowWidth() / 2 - 200, game->getWindowHeight() / 4, 100, 75,game, view));
}

void MenuState::registerCommands()
{
   commandFactory->add(new NextStateCommand());
   commandFactory->add(new CommandExit());
}

void MenuState::update()
{
   for (auto b : buttons) {
        b->update();
   }
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
  /*  for (auto b : buttons) {
        b->draw();
    }*/
}

void MenuState::next()
{
    for (auto b : buttons) {
        delete b;
        b = nullptr;
    }
    cout << "Next State " << endl;
    game->setState(new PlayingState(game, nullptr));
    delete this;
}
