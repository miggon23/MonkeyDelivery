#pragma once

#include "State.h"

class GameOverState : public State
{ // CLASE PARA CINEMÁTICA O MODO FINAL DE JUEGO
private:
	bool winMessage = false;
	
public:
	GameOverState(Game* game);
	~GameOverState() = default;

	inline void update()override {};
	void draw()override;
	inline void next()override {};

	string getStateName() const {
		return "GameOver state";
	};

	void registerCommands()override;
};