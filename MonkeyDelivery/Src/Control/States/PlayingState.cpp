#include "PlayingState.h"

#include "../../Logic/Game.h"

//#include "../NextStateCommand.h"
#include "../CommandMove.h"
#include "../CommandRun.h"
#include "../CommandInteract.h"
#include "../CommandExit.h"
#include "../PauseCommand.h"
#include "../InventoryCommand.h"
#include "../FastTextCommand.h"

#include "../States/MenuState.h"


PlayingState::PlayingState(Game* game, ViewController* v) : State(game,v) {
    registerCommands();
    game->start();
}

void PlayingState::registerCommands() {

    //commandFactory->add(new NextStateCommand());
    commandFactory->add(new CommandMove());
    commandFactory->add(new CommandExit());
    commandFactory->add(new CommandInteract());
    commandFactory->add(new CommandRun());
    commandFactory->add(new PauseCommand());
    commandFactory->add(new InventoryCommand());
    commandFactory->add(new FastTextCommand());
}

void PlayingState::update() {
    game->update();
}

void PlayingState::draw() {
    game->draw();
}

void PlayingState::next() {
    cout << "Next State " << endl;
    //game->setState(new MenuState(game));
    delete this;
}