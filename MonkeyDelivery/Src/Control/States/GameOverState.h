#pragma once

#include "State.h"

class GameOverState : public State
{ 
	// CLASE PARA CINEMÁTICA O MODO FINAL DE JUEGO
private:
	bool winMessage = false;
	std::map< int, TextureName> textureMap;
	int NUM_ELEMS = 83;
public:
	GameOverState(Game* game);
	~GameOverState() = default;
	inline void update()override {}
	inline void draw() override {}
	void renderCinematic(int i);
	inline void next()override {}

	string getStateName() const {
		return "GameOver state";
	};
	void registerCommands()override;
};