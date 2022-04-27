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

	int wPlayer_ = 16,
		hPlayer_ = 18,
		x1 = 16,
		playerFrameSpeed = 200;
	
	//Murcielago	
	int wBat_ = 35,
		hBat_ = 30; 
	//Gato
	int wCat_ = 100,
		hCat_ = 100;

	//Toro
	int wBull_ = 100,
		hBull_ = 100;

	//Escorpion
	int wScorpion_ = 18,
		hScorpion_ = 18;

	//Planta
	int wPlant_ = 55,
		hPlant_ = 55;

public:

	struct LastDir
	{
		int x;
		int y;
	};
	LastDir lastDir;

	inline AnimationManager() : game_(nullptr) { lastDir = {0,0}; };
	inline AnimationManager(Game* game) :game_(game) { lastDir = { 0,0 }; };
	inline ~AnimationManager() { timer_ = nullptr; cout << "animationManager Deleted" << endl; };

	//JUGADOR
	inline PlayerState setState(PlayerState state) { return playerState_ = state; };
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
			texturaRect.y = 18;
			tex->render(texturaRect, player);
			if (timer_->TimeScale() - timer >= playerFrameSpeed) {
				x1 += 16;
				if (texturaRect.x >= playerLimit- wPlayer_) {
					texturaRect.x = 0;
					x1 = 0;
				}
				timer = timer_->TimeScale();
			}
		}

		else if (playerState_ == GoToSleep) {

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
			//las x
			switch (newDir.x)
			{
			case 1: //Derecha
				texturaRect.y = 54 + 90;
				break;
			case -1: //Izquierda
				texturaRect.y = 36 + 90;
				break;
			default:
				break;
			}
			//las y
			switch (newDir.y)
			{
			case 1: //Abajo
				texturaRect.y = 0 + 90;
				break;
			case -1: //Arriba
				texturaRect.y = 72+ 90;
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
	}
	//MURCIELAGO
	inline int getWidthBat() { return wBat_; };
	inline int getHeightBat() { return hBat_; };
	/// <summary>
	/// Recortar una imagen del SpriteSheet del murcielago
	/// </summary>
	/// <param name="bat">COLLIDER DEL MUERCIELAGO</param>
	/// <param name="texturaRect">textureRect DEL MURCIELAGO(es una variable es lo q vamos a recortar de la sprite sheet)</param>
	/// <param name="tex"> Textura del muercielago</param>
	/// <param name="timer">variable timerAnimation para que me cambie la imagen cada cierto numero de ticks</param>
	inline void getFrameImageBat(SDL_Rect bat, SDL_Rect& texturaRect, Texture* tex, float& timer, SDL_RendererFlip flip) {
		if (timer_->TimeScale() - timer >= 250) {
			texturaRect.x += wBat_;
			if (texturaRect.x > 35) {
				texturaRect.x = 0;
			}
			timer = timer_->TimeScale();
		}
		tex->render(texturaRect, bat, 0, nullptr, flip);
	}
	//GATO
	inline int getWidthCat() { return wCat_; };
	inline int getHeightcat() { return hCat_; };
	inline void getFrameImageCat(SDL_Rect cat, SDL_Rect& texturaRect, Texture* tex, float& timer, SDL_RendererFlip flip) {
		if (timer_->TimeScale() - timer >= 450) {
			texturaRect.y += hCat_;
			if (texturaRect.y >= 200) {
				texturaRect.y = 0;
			}
			timer = timer_->TimeScale();
		}
		tex->render(texturaRect, cat, 0, nullptr, flip);
	}

	//TORO
	inline int getWidthBull() { return wBull_; };
	inline int getHeigthBull() { return hBull_; };
	inline void getFrameImageBull(SDL_Rect bull, SDL_Rect& texturaRect, Texture* tex, float& timer, SDL_RendererFlip flip) {
		if (timer_->TimeScale() - timer >= 350) {
			texturaRect.x += wBull_;
			if (texturaRect.y >= 100 && texturaRect.x >= 200) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			if (texturaRect.x >= 200) {
				texturaRect.x = 0;
				texturaRect.y += hBull_;
			}

			timer = timer_->TimeScale();

		}
		tex->render(texturaRect, bull, 0, nullptr, flip);
	};

	//ESCORPION
	inline int getWidthScorpion() { return wScorpion_; };
	inline int getHeigthScorpion() { return hScorpion_; };
	inline void getFrameImageScorpion(SDL_Rect scorpion, SDL_Rect& texturaRect, Texture* tex, float& timer, SDL_RendererFlip flip) {
		if (timer_->TimeScale() - timer >= 200) {
			texturaRect.x += wScorpion_;
			if (texturaRect.x >= 144) {
				texturaRect.x = 0;
			}
			timer = timer_->TimeScale();
		}
		tex->render(texturaRect, scorpion, 0, nullptr, flip);

	};

	//PLANTA
	inline int getWidthPlant() { return wPlant_; };
	inline int getHeigthPlant() { return hPlant_; };
	inline void getFrameImagePlant(SDL_Rect plant, SDL_Rect& texturaRect, Texture* tex, float& timer, SDL_RendererFlip flip) {
		if (timer_->TimeScale() - timer >= 150) {
			texturaRect.x += wPlant_;
			if (texturaRect.y >= 55 && texturaRect.x >= 220) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			if (texturaRect.x >= 220) {
				texturaRect.x = 0;
				texturaRect.y += hPlant_;
			}
			timer = timer_->TimeScale();
		}
		tex->render(texturaRect, plant, 0, nullptr, flip);
	};

	//MENSAJE PANEL MISIONES
	inline void getFrameImageMission(SDL_Rect plant, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		if (timer_->TimeScale() - timer >= 150) {
			texturaRect.x += 200;
			if (texturaRect.x >= 400) {
				texturaRect.x = 0;
			}
			timer = (int)timer_->TimeScale();
		}
		tex->render(texturaRect, plant);
	};
};