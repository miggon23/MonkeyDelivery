#pragma once

#include "State.h"

class GameOverState : public State
{ 
	// CLASE PARA CINEMÁTICA O MODO FINAL DE JUEGO
private:
	bool winMessage = false;
	std::map< int, TextureName> textureMap;
	int NUM_ELEMS = 83;
	int i = 1;
	Uint32 interval = 70000;

	Uint32 startTicks;
public:
	GameOverState(Game* game);
	~GameOverState() = default;
	inline void update();
	inline void draw() override {}
	void renderCinematic(int i);
	inline void next()override {}

	string getStateName() const {
		return "GameOver state";
	};
	void registerCommands()override;
};