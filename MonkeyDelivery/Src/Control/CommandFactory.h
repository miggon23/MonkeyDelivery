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

    Command* getCommand(SDL_Event& event) {       
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