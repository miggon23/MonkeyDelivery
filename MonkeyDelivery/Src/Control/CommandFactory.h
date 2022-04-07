#pragma once
#include "Command.h"
#include "../Logic/Game.h"
#include "CommandExit.h"

class CommandFactory
{
	vector<Command*> availableCommands;
	Game* game;

public:
	CommandFactory(Game* g) {
		game = g;
	};
    ~CommandFactory() {
        for (auto c : availableCommands)
            delete c;
        cout << "COMANDOS ELIMINADOS" << endl;
    }

    /*vector<Command*> getCommand(SDL_Event& event) {
        vector<Command*> executeCommands;
        for (auto c : availableCommands) {
            if (c->parse(event)) executeCommands.push_back(c);
        }
        return executeCommands;
    }*/

    Command* getCommand(SDL_Event& event) {
        Command* executeCommands;
        for (auto c : availableCommands) {
            if (c->parse(event)) return c;
        }
        return nullptr;
    }

    void add(Command* c) {
        c->bind(game);
        availableCommands.push_back(c);
    }
};