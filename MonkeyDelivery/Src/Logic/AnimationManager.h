#pragma once
#include "../View/Texture.h"
#include "../View/TextureContainer.h"

class Game;
class Timer;

class AnimationManager
{
public:
	enum PlayerState { Sleeping, GoToSleep, Running, Scared, Idle };

private:
	Game* game_;
	//Player	
	PlayerState playerState_ = Running;

	int limit = 600;
	int playerLimit = 64;
	bool isTired_;
	bool isScared_;

	int wPlayer_ = 16,
		hPlayer_ = 18,
		x1 = 16,
		playerFrameSpeed = 200;
	
public:

	struct LastDir
	{
		int x;
		int y;
	};
	LastDir lastDir;

	inline AnimationManager() : game_(nullptr) { lastDir = { 0,0 }; isTired_ = false; isScared_ = false; };
	inline AnimationManager(Game* game) :game_(game) { lastDir = { 0,0 }; isTired_ = false; isScared_ = false;};
	inline ~AnimationManager() {  };

	//JUGADOR
	inline PlayerState setState(PlayerState state) { return playerState_ = state; };
	inline void setIsTired(bool t) { isTired_ = t; }
	inline void setIsScared(bool s) { isScared_ = s; }
	inline int getWidthPlayer() { return wPlayer_; };
	inline int getHeightPlayer() { return hPlayer_; };
	void getFrameImagePlayer(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, float& timer, LastDir newDir);

	//ENEMIGOS, PANEL DE MISIONES Y TIENDA
	void getFrameImage(SDL_Rect rect, SDL_Rect& texturaRect, Texture* tex, float& timer, SDL_RendererFlip flip,
		int w, int h, int maxX, int maxY, int time);
	
};