#include "TestingState.h"
#include "../../Logic/Game.h"


TestingState::TestingState(Game* game) : State(game) {
    registerCommands();
}

void TestingState::registerCommands() {
   //commandFactory->add(new NextStateCommand());
}

void TestingState::update() {
}

void TestingState::draw() {
    int x = game->getWindowWidth() / 2 - 100;
    int y = game->getWindowHeight() / 2 - 50;

    vector<string> texts = {
            "Welcome to Monkey Delivery"
    };
}

void TestingState::next() {
    cout << "Next State " << endl;
    //game->setState(new Level_0_State(game));
    delete this;
}