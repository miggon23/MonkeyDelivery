#pragma once
#include "../View/Texture.h"
#include "../View/TextureContainer.h"

class Game;
class AnimationManager
{
public:
	enum PlayerState {Sleeping, GoToSleep, Running, Scared };

private:
	Game* game_;
	//Player	
	PlayerState playerState_= Running;
	

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
	
public:

	struct LastDir
	{
		int x;
		int y;
	};
	LastDir lastDir;
	inline AnimationManager() {};
	inline AnimationManager(Game* game) :game_(game) {		
	};
	inline ~AnimationManager() { cout << "animationManager Deleted" << endl; };
	//JUGADOR
	inline PlayerState setState(PlayerState state) { return playerState_ = state; };
	inline int getWidthPlayer() { return wPlayer_; };
	inline int getHeightPlayer() { return hPlayer_; };

	inline void getFrameImagePlayer(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer/*,PlayerState state*/,  LastDir newDir) {

		if (playerState_==Running) {
			if (lastDir.x != newDir.x || lastDir.y != newDir.y) //Si la direccion cambia (da igual de que componente)
			{
				texturaRect.x = 0;
				lastDir = newDir;
			}	
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

			if (SDL_GetTicks() - timer >= 500) {
				texturaRect.x += 100;
				if (texturaRect.x >= limit) {
					texturaRect.x = 0;
				}
				timer = SDL_GetTicks();
			}
		}
		else if (playerState_== GoToSleep) {
			
		}
		else if(playerState_== Scared){
			texturaRect.x = x1;
			texturaRect.y = 300;
			tex->render(texturaRect, player);

			if (SDL_GetTicks() - timer >= 500) {
				x1 += 100;
				if (texturaRect.x >= 500) {
					texturaRect.x = 100;
					x1 = 100;
				}
				timer = SDL_GetTicks();
			}
		}
	}
	inline void Sleep(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		texturaRect.x = 0; texturaRect.y = 600;
		tex->render(texturaRect, player);
		if (SDL_GetTicks() - timer >= 500) {
			wPlayer_ += 100;
			if (wPlayer_ >= 600) {
				wPlayer_ = 0; texturaRect.x = 0;
			}
			timer = SDL_GetTicks();
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
	inline void getFrameImageBat(SDL_Rect bat,SDL_Rect &texturaRect, Texture* tex,int &timer) {
		if (SDL_GetTicks() - timer >= 200) {
			texturaRect.x += wBat_;
			if (texturaRect.x >= 200/*&&texturaRect.y<300*/) {
				texturaRect.x = 0;
				texturaRect.y += hBat_;
			}
			if (texturaRect.y >= 200&& texturaRect.x>=100) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			timer = SDL_GetTicks();
			//cout << texturaRect.x << " " << texturaRect.y << endl;
		}
		tex->render(texturaRect, bat);		
	}	
	//GATO
	inline int getWidthCat() { return wCat_; };
	inline int getHeightcat() { return hCat_; };
	inline void getFrameImageCat(SDL_Rect cat, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		if (SDL_GetTicks() - timer >= 450) {
			texturaRect.y += hCat_;			
			if (texturaRect.y >= 200) {
				texturaRect.y = 0; 
			}
			timer = SDL_GetTicks();			
		}
		tex->render(texturaRect, cat);		
	}

	//TORO
	inline int getWidthBull() { return wBull_; };
	inline int getHeigthBull() { return hBull_; };
	inline void getFrameImageBull(SDL_Rect bull, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		if (SDL_GetTicks() - timer >= 500) {
			texturaRect.x += wBull_;
			if (texturaRect.y >= 100 && texturaRect.x >= 200) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			if (texturaRect.x >= 200) {
				texturaRect.x = 0;
				texturaRect.y += hBull_;
			}
			
			timer = SDL_GetTicks();
			
		}
		tex->render(texturaRect, bull);
	};
};

