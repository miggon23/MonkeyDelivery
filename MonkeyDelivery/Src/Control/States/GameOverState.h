#pragma once

#include "State.h"

class GameOverState : public State
{ 
	// CLASE PARA CINEMÁTICA O MODO FINAL DE JUEGO
private:
	std::map< int, TextureName> textureMap;
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(), (int)game->getWindowHeight() };
	int NUM_ELEMS = 83;
	int i = 1;
	//int size = game->getWindowWidth() + 1500;
	//int decrease = 30;
	Uint32 interval = 200;
	Uint32 startTicks;
	//bool completed = false;
	
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