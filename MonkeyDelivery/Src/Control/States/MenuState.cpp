#include "MenuState.h"
#include "../../Logic/Game.h"

#include "../NextStateCommand.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../States/PlayingState.h"
#include "../Buttons/Exit.h"
#include "../Buttons/Start.h"
#include "../Buttons/Options.h"




MenuState::MenuState(Game* game) : State(game){
    registerCommands();
    addButton(new Start(game->getWindowWidth() / 2 - 100, game->getWindowHeight() - 250, 100, 75, game));  
    addButton(new Options(game->getWindowWidth() / 2 - 100, game->getWindowHeight() - 100, 100, 75, game));  
}

MenuState::~MenuState(){
}

void MenuState::registerCommands()
{
   commandFactory->add(new CommandClick());
   
   commandFactory->add(new CommandExit());
}

void MenuState::update(){
}

void MenuState::draw()
{
    int x = game->getWindowWidth() / 2 - 250;
    int y = game->getWindowHeight() / 2 - 100;

    vector<string> texts = {
            "Welcome to Monkey Delivery"
    };

    game->renderText(texts, x, y, 75, 75);
    for (auto b :getButtonsUI()) {
        b->draw();
    }
}

void MenuState::next()
{
    for (auto b : buttonsUI) {
        delete b;
        b = nullptr;
    }
    cout << "Next State " << endl;
    game->setState(new PlayingState(game));
    delete this;
}
