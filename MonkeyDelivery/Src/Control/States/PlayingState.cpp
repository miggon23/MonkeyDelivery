#include "PlayingState.h"

#include "../../Logic/Game.h"

//#include "../NextStateCommand.h"
#include "../CommandMove.h"
#include "../CommandRun.h"
#include "../CommandInteract.h"
#include "../CommandExit.h"
#include "../CommandClick.h"
#include "../InventoryCommand.h"
#include "../InteractDialogueBoxCommand.h"
#include "../UI/Buttons/Back.h"
#include "../UI/Buttons/Pause.h"



#include "../States/MenuState.h"


PlayingState::PlayingState(Game* game) : State(game) {
    registerCommands();
    game->start();
    addButton(new Pause(game->getWindowWidth()- 80, 30, 60, 60, game));
}

void PlayingState::registerCommands() {

    //commandFactory->add(new NextStateCommand());
    commandFactory->add(new CommandMove());
    commandFactory->add(new CommandExit());
    commandFactory->add(new CommandInteract());
    commandFactory->add(new CommandRun());
    commandFactory->add(new CommandClick());
    //commandFactory->add(new PauseCommand());
    commandFactory->add(new InventoryCommand());
    commandFactory->add(new InteractDialogueBoxCommand());
}

void PlayingState::update() {
    game->update();
}

void PlayingState::draw() {
    game->draw();

    for (auto b : getButtonsUI()) {
        b->draw();
    }
    game->DrawBrightness();
}

void PlayingState::next() {
    cout << "Next State " << endl;
    //game->setState(new MenuState(game));
    delete this;
}