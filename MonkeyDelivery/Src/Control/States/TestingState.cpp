#include "TestingState.h"

#include "../NextStateCommand.h"
#include "../../Logic/Game.h"


TestingState::TestingState(Game* game) : State(game) {
    registerCommands();
}

void TestingState::registerCommands() {
   commandFactory->add(new NextStateCommand());
}

void TestingState::update() {
}

void TestingState::draw() {
    
}

void TestingState::next() {
    cout << "Next State " << endl;
    //game->setState(new Level_0_State(game));
    delete this;
}