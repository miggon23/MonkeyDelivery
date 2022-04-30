#pragma once
#include "../View/Texture.h"
#include "../View/TextureContainer.h"
#include "../utils/Timer.h"
class Game;

class AnimationManager
{
public:
	enum PlayerState { Sleeping, GoToSleep, Running, Scared, Idle };

private:
	Game* game_;
	//Player	
	PlayerState playerState_ = Running;

	Timer* timer_ = Timer::Instance();
	int limit = 600;
	int playerLimit = 64;
	bool isTired_;

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

	inline AnimationManager() : game_(nullptr) { lastDir = { 0,0 }; isTired_ = false; };
	inline AnimationManager(Game* game) :game_(game) { lastDir = { 0,0 }; isTired_ = false;};
	inline ~AnimationManager() { timer_ = nullptr; cout << "animationManager Deleted" << endl; };

	//JUGADOR
	inline PlayerState setState(PlayerState state) { return playerState_ = state; };
	inline bool getIsTired() { return isTired_; }
	inline void setIsTired(bool t) { isTired_ = t; }
	inline int getWidthPlayer() { return wPlayer_; };
	inline int getHeightPlayer() { return hPlayer_; };
	inline void getFrameImagePlayer(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, float& timer, LastDir newDir) {
		//Si la direccion cambia (da igual de que componente)
		if (lastDir.x != newDir.x || lastDir.y != newDir.y) {
			texturaRect.x = 0;
			lastDir = newDir;
			if (timer_->TimeScale() - timer >= playerFrameSpeed) {
				texturaRect.x += 16;
				if (texturaRect.x >= playerLimit) {
					texturaRect.x = 0;
				}
				timer = timer_->TimeScale();
			}
		}

		if (playerState_==Running) 
		{
			//las x
			switch (newDir.x)
			{
			case 1: //Derecha
				texturaRect.y = 54;
				break;
			case -1: //Izquierda
				texturaRect.y = 36;
				break;
			default:
				break;
			}
			//las y
			switch (newDir.y)
			{
			case 1: //Abajo
				texturaRect.y = 0;
				break;
			case -1: //Arriba
				texturaRect.y = 72;
				break;
			default:
				break;
			}

			tex->render(texturaRect, player);

			if (timer_->TimeScale() - timer >= playerFrameSpeed) {
				texturaRect.x += 16;
				if (texturaRect.x >= playerLimit) {
					texturaRect.x = 0;
				}
				timer = timer_->TimeScale();
			}
		}
		else if (playerState_ == Idle) {
			texturaRect.x = x1;
			if(isTired_) texturaRect.y = 108;
			else texturaRect.y = 18;
			tex->render(texturaRect, player);
			if (timer_->TimeScale() - timer >= playerFrameSpeed) {
				x1 += 16;
				if (texturaRect.x >= playerLimit- wPlayer_) {
					texturaRect.x = 0;
					x1 = 0;
				}
				timer = timer_->TimeScale();
			}
			isTired_ = false;
		}
		else if (playerState_ == GoToSleep) {

			//las x
			switch (newDir.x)
			{
			case 1: //Derecha
				texturaRect.y = 144;
				break;
			case -1: //Izquierda
				texturaRect.y = 126;
				break;
			default:
				break;
			}
			//las y
			switch (newDir.y)
			{
			case 1: //Abajo
				texturaRect.y = 90;
				break;
			case -1: //Arriba
				texturaRect.y = 162;
				break;
			default:
				break;
			}

			texturaRect.x = x1;
			tex->render(texturaRect, player);

			if (timer_->TimeScale() - timer >= playerFrameSpeed) {
				x1 += 16;
				if (texturaRect.x >= playerLimit-wPlayer_) {
					texturaRect.x = 0;
					x1 = 0;
				}
				timer = timer_->TimeScale();
			}
		}
		else if (playerState_ == Scared) {
			texturaRect.x = 0;
			texturaRect.y = 90;
			tex->render(texturaRect, player);

			if (timer_->TimeScale() - timer >= playerFrameSpeed) {
				x1 += 16;
				if (texturaRect.x >= playerLimit) {
					texturaRect.x = 0;
					x1 = 16;
				}
				timer = timer_->TimeScale();
			}
		}
		if (playerState_ == Sleeping)
		{
			/*texturaRect.x = 0;
			texturaRect.y = 90;
			tex->render(texturaRect, player);

			if (timer_->TimeScale() - timer >= playerFrameSpeed) {
				x1 += 16;
				if (texturaRect.x >= playerLimit) {
					texturaRect.x = 0;
					x1 = 16;
				}
				timer = timer_->TimeScale();
			}*/
			
		}
	}

	//ENEMIGOS Y PANEL DE MISIONES
	inline void getFrameImage(SDL_Rect rect, SDL_Rect& texturaRect, Texture* tex, float& timer, SDL_RendererFlip flip,
		int w, int h, int maxX, int maxY, int time) {
		if (timer_->TimeScale() - timer >= time) {
			texturaRect.x += w;
			if (texturaRect.y >= maxY && texturaRect.x >= maxX) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			if (texturaRect.x >= maxX) {
				texturaRect.x = 0;
				texturaRect.y += h;
			}
			timer = timer_->TimeScale();
		}
		tex->render(texturaRect, rect, 0, nullptr, flip);
	}
	
};