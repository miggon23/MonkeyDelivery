#pragma once
#include "../View/Texture.h"
#include "../View/TextureContainer.h"

class Game;
class AnimationManager
{
public:
	enum PlayerState { /*Static = 0,*/ Down = 0, Left, Right, Up};
private:
	Game* game_;
	//Player	
	PlayerState lastPlayerState;
	int wPlayer_=0,
		hPlayer_=100;
	pair<int, int> velLast;
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
	inline AnimationManager() {};
	inline AnimationManager(Game* game) :game_(game) {		
	};
	inline ~AnimationManager() { cout << "animationManager Deleted" << endl; };
	//JUGADOR
	inline int getWidthPlayer() { return wPlayer_+100; };
	inline int getHeightPlayer() { return hPlayer_; };
	//inline void StaticFrame(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer) {
	//	texturaRect.y = 0; texturaRect.x = wPlayer_;		
	//	tex->render(texturaRect, player);
	//	if (SDL_GetTicks() - timer >= 500) {
	//		wPlayer_ += 100;
	//		if (wPlayer_ >= 600) { 
	//			wPlayer_ = 0; texturaRect.x = 0;
	//		}			
	//		timer = SDL_GetTicks();
	//	}
	//}
	//inline void UpFrame(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer) {
	//	texturaRect.y = 100; texturaRect.x = wPlayer_;
	//	tex->render(texturaRect, player);
	//	if (SDL_GetTicks() - timer >= 500) {
	//		wPlayer_ += 100;
	//		if (wPlayer_ >= 600) {
	//			wPlayer_ = 0; texturaRect.x = 0;
	//		}
	//		timer = SDL_GetTicks();
	//	}
	//}
	//*inline void DownFrame(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer) {
	//	texturaRect.y = 200; texturaRect.x = wPlayer_;
	//	tex->render(texturaRect, player);
	//	if (SDL_GetTicks() - timer >= 500) {
	//		wPlayer_ += 100;
	//		if (wPlayer_ >= 600) {
	//			wPlayer_ = 0; texturaRect.x = 0;
	//		}
	//		timer = SDL_GetTicks();
	//	}
	//}*/
	//inline void RightFrame(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer) {
	//	texturaRect.y = 500; texturaRect.x = wPlayer_;
	//	tex->render(texturaRect, player);
	//	if (SDL_GetTicks() - timer >= 500) {
	//		wPlayer_ += 100;
	//		if (wPlayer_ >= 600) {
	//			wPlayer_ = 0; texturaRect.x = 0;
	//		}
	//		timer = SDL_GetTicks();
	//	}
	//}
	//inline void LeftFrame(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer) {
	//	texturaRect.y = 400; texturaRect.x = wPlayer_;
	//	tex->render(texturaRect, player);
	//	if (SDL_GetTicks() - timer >= 500) {
	//		wPlayer_ += 100;
	//		if (wPlayer_ >= 600) {
	//			wPlayer_ = 0; texturaRect.x = 0;
	//		}
	//		timer = SDL_GetTicks();
	//	}
	//}
	inline void getFrameImagePlayer(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer,PlayerState state,pair<int,int>vel) {
		/*if (lastPlayerState != state) {
		wPlayer_ = 0;
		lastPlayerState = state;
	}*/
		if (velLast.first != vel.first || velLast.second != vel.second) {
			wPlayer_ = 0;
			//lastPlayerState = state;
			velLast = vel;			
		}	
		//las x
		switch (vel.first)
		{
		case 1:
			texturaRect.y = 500;
			break;
		case -1:
			texturaRect.y = 400;
			break;
		default:
			break;
		}
		//las y
		switch (vel.second)
		{
		case 1:
			texturaRect.y = 0;
			break;
		case -1:
			texturaRect.y = 100;
			break;
		default:
			break;
		}
	/*	switch (state)
		{		
		case Left:
			texturaRect.y = 400;			
			break;
		case Right:
			texturaRect.y = 500;			
			break;
		case Up:
			texturaRect.y = 100;			
			break;
		case Down:
			texturaRect.y = 0;			
			break;
		default:
			break;
		}*/
	    texturaRect.x = wPlayer_;
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

