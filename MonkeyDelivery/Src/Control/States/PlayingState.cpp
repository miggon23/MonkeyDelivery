#include "PlayingState.h"

#include "../../Logic/Game.h"

#include "../CommandMove.h"
#include "../CommandRun.h"
#include "../CommandInteract.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../InventoryCommand.h"
#include "../InteractDialogueBoxCommand.h"
#include "../MapCommand.h"
#include "../PauseCommand.h"

#include "../UI/Buttons/Back.h"
#include "../UI/Buttons/Pause.h"

#include "../States/MenuState.h"


PlayingState::PlayingState(Game* game) : State(game) {
    registerCommands();
    if (game->getPlayer() == nullptr) {
        game->start();
    }
    else {
        game->restart();
    }
    addButton(new Pause((int)game->getWindowWidth()- 80, 30, 60, 60, game));
}

void PlayingState::registerCommands() {
    
    commandFactory->add(new CommandMove());
    commandFactory->add(new CommandExit());
    commandFactory->add(new CommandInteract());
    commandFactory->add(new CommandRun());
    commandFactory->add(new CommandClick());
    commandFactory->add(new PauseCommand());
    commandFactory->add(new InventoryCommand());
    commandFactory->add(new InteractDialogueBoxCommand());
    commandFactory->add(new MapCommand());
}

void PlayingState::onEnterState()
{
    game->getTimer()->UnPause();
    game->getPlayer()->resumePowerUps();
}

void PlayingState::draw() {
    game->draw();

    for (auto b : getButtonsUI()) {
        b->draw();
    }
}

void PlayingState::next() {
    cout << "Next State " << endl;
    delete this;
}