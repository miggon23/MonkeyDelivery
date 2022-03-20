#pragma once
#include "../View/Texture.h"
#include "../View/TextureContainer.h"
#include "../Utils/Timer.h"
class Game;
class AnimationManager
{
public:
	enum PlayerState {Sleeping, GoToSleep, Running, Scared };

private:
	Game* game_;
	//Player	
	PlayerState playerState_= Running;
	
	Timer* timer_ = Timer::Instance();	
	int limit = 600;

	int wPlayer_=100,
		hPlayer_=100,
		x1=100;
	
	
	//Murcielago	
	int wBat_ = 100,
		hBat_ = 100;
	//Gato
	int wCat_=100,
		hCat_=100;

	//Toro
	int wBull_ = 100,
		hBull_ = 100;

	//Escorpion
	int wScorpion_ = 100,
		hScorpion_ = 100;

	//Planta
	int wPlant_ = 100,
		hPlant_ = 100;
	
public:

	struct LastDir
	{
		int x;
		int y;
	};
	LastDir lastDir;
	inline AnimationManager() {  };
	inline AnimationManager(Game* game) :game_(game) {		
	};
	inline ~AnimationManager() { timer_ = nullptr; cout << "animationManager Deleted" << endl; };
	//JUGADOR
	inline PlayerState setState(PlayerState state) { return playerState_ = state; };
	inline int getWidthPlayer() { return wPlayer_; };
	inline int getHeightPlayer() { return hPlayer_; };

	inline void getFrameImagePlayer(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer/*,PlayerState state*/,  LastDir newDir) {
		if (lastDir.x != newDir.x || lastDir.y != newDir.y){//Si la direccion cambia (da igual de que componente)
			texturaRect.x = 0;
			lastDir = newDir;
		}
		if (playerState_==Running) {
			
			//las x
			switch (newDir.x)
			{
			case 1: //Derecha
				texturaRect.y = 500;
				break;
			case -1: //Izquierda
				texturaRect.y = 400;
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
				texturaRect.y = 100;
				break;
			default:
				break;
			}

			tex->render(texturaRect, player);

			if (timer_->TimeScale() - timer >= 20) {
				texturaRect.x += 100;
				if (texturaRect.x >= limit) {
					texturaRect.x = 0;
				}
				timer = timer_->TimeScale();
			}
		}
		else if (playerState_== GoToSleep) {
			
		}
		else if(playerState_== Scared){
			texturaRect.x = x1;
			texturaRect.y = 200;
			tex->render(texturaRect, player);

			if (timer_->TimeScale() - timer >= 20) {
				x1 += 100;
				if (texturaRect.x >= 500) {
					texturaRect.x = 100;
					x1 = 100;
				}
				timer = timer_->TimeScale();
			}
		}
		else if (playerState_ == Sleeping) {			
			texturaRect.y = 600;			
			tex->render(texturaRect, player);
			if (timer_->TimeScale() - timer >= 20) {
				texturaRect.x += 100;
				if (texturaRect.x >= 200) {
					texturaRect.x = 0;				
				}
				timer = timer_->TimeScale();
				cout << texturaRect.x << endl;
			}
			
		}
	}
	inline void Sleep() {
		playerState_ = Sleeping;
	}
	inline void WakeUp() {
		playerState_ = Running;
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
	inline void getFrameImageBat(SDL_Rect bat,SDL_Rect &texturaRect, Texture* tex,int &timer) {
		if (timer_->TimeScale() - timer >= 25) {
			texturaRect.x += wBat_;
			if (texturaRect.x >= 200/*&&texturaRect.y<300*/) {
				texturaRect.x = 0;
				texturaRect.y += hBat_;
			}
			if (texturaRect.y >= 200&& texturaRect.x>=100) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			timer = timer_->TimeScale();
			//cout << texturaRect.x << " " << texturaRect.y << endl;
		}
		tex->render(texturaRect, bat);		
	}	
	//GATO
	inline int getWidthCat() { return wCat_; };
	inline int getHeightcat() { return hCat_; };
	inline void getFrameImageCat(SDL_Rect cat, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		if (timer_->TimeScale() - timer >=30) {
			texturaRect.y += hCat_;			
			if (texturaRect.y >= 200) {
				texturaRect.y = 0; 
			}
			timer = timer_->TimeScale();
		}
		tex->render(texturaRect, cat);		
	}

	//TORO
	inline int getWidthBull() { return wBull_; };
	inline int getHeigthBull() { return hBull_; };
	inline void getFrameImageBull(SDL_Rect bull, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		if (timer_->TimeScale() - timer >= 20) {
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
		tex->render(texturaRect, bull);
	};

	//ESCORPION
	inline int getWidthScorpion() { return wScorpion_; };
	inline int getHeigthScorpion() { return hScorpion_; };
	inline void getFrameImageScorpion(SDL_Rect scorpion, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		if (timer_->TimeScale() - timer >= 20) {
			texturaRect.x += wScorpion_;
			if (texturaRect.y >= 200 && texturaRect.x >= 200) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			if (texturaRect.x >= 200) {
				texturaRect.x = 0;
				texturaRect.y += hScorpion_;
			}
			timer = timer_->TimeScale();
		}
		tex->render(texturaRect, scorpion);
	};

	//PLANTA
	inline int getWidthPlant() { return wPlant_; };
	inline int getHeigthPlant() { return hPlant_; };
	inline void getFrameImagePlant(SDL_Rect plant, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		if (timer_->TimeScale() - timer >= 20) {
			texturaRect.x += wPlant_;
			if (texturaRect.y >= 400 && texturaRect.x >= 100) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			if (texturaRect.x >= 200) {
				texturaRect.x = 0;
				texturaRect.y += hPlant_;
			}
			timer = timer_->TimeScale();
		}
		tex->render(texturaRect, plant);
	};
};

