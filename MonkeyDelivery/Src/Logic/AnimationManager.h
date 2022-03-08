#pragma once
#include "../View/Texture.h"
#include "../View/TextureContainer.h"

class Game;
class AnimationManager
{
public:
	enum PlayerState { Static = 0, Left, Right, Up, Down };
private:
	Game* game_;
	//Player	
	PlayerState lastPlayerState;
	int wPlayer_=1475,
		hPlayer_=1540;
	int xStaticFront_=0,
		yStaticFront_= 1600;
	int xStaticBack_ = 0,
		yStaticBack = 0;

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
	inline void StaticFrame(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer) {
		//accedo a las correspondientes frames
		texturaRect.x = xStaticFront_;
		texturaRect.y = yStaticFront_;		
		if (texturaRect.x >= 3 * wPlayer_) {
			texturaRect.x = 0;
			xStaticFront_ = 0;
		}
		tex->render(texturaRect, player);
		if (SDL_GetTicks() - timer >= 500) {
			xStaticFront_ += wPlayer_;
			timer = SDL_GetTicks();
			cout << "actulizar frame" << endl;
		}
	}
	inline void getFrameImagePlayer(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, int& timer,PlayerState state) {
		if (lastPlayerState != state) {			
			xStaticFront_ = 0;			
			lastPlayerState = state;
		}
		switch (state)
		{
		case Static:
			StaticFrame(player,texturaRect,tex,timer);
			break;
		case Left:
			break;
		case Right:
			break;
		case Up:
			break;
		case Down:
			break;
		default:
			break;
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
		if (SDL_GetTicks() - timer >= 200) {
			texturaRect.x += wBull_;
			if (texturaRect.x >= 200) {
				texturaRect.x = 0;
				texturaRect.y += hBull_;
			}
			if (texturaRect.y >= 100 && texturaRect.x >= 100) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			timer = SDL_GetTicks();
		}
		tex->render(texturaRect, bull);
	};
};

