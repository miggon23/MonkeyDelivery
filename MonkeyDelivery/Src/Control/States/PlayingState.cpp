#include "PlayingState.h"

#include "../NextStateCommand.h"
#include "../../Logic/Game.h"

#include "../CommandMove.h"
#include "../CommandRun.h"
#include "../CommandInteract.h"
#include "../CommandExit.h"

PlayingState::PlayingState(Game* game) : State(game) {
    registerCommands();
    game->start();
}

void PlayingState::registerCommands() {

    commandFactory->add(new NextStateCommand());
    commandFactory->add(new CommandMove());
    commandFactory->add(new CommandExit());
    commandFactory->add(new CommandInteract());
    commandFactory->add(new CommandRun());
}

void PlayingState::update() {
    game->update();
}

void PlayingState::draw() {
    game->draw();
}

void PlayingState::next() {
    cout << "Next State " << endl;
    //game->setState(new Level_0_State(game));
    delete this;
}