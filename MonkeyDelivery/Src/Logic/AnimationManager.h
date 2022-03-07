#pragma once
#include "../View/Texture.h"
#include "../View/TextureContainer.h"

class Game;
class AnimationManager
{
	Game* game_;
	//Player
	int wPlayer_=100,
		hPlayer_=100;	
	//Murcielago	
	int wBat_ = 100,
		hBat_ = 100;
	//Gato
	int wCat_=100,
		hCat_=100;
	
public:
	inline AnimationManager() {};
	inline AnimationManager(Game* game) :game_(game) {		
	};
	inline ~AnimationManager() { cout << "animationManager Deleted" << endl; };
	inline void getFrameImagePlayer(SDL_Rect player, Texture* tex) {
		
	}
	//MURCIELAGO
	inline int getWeightBat() { return wBat_; };
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
			if (texturaRect.x >= 200) {
				texturaRect.x = 0;
				texturaRect.y += hBat_;
			}
			if (texturaRect.y >= 200) {
				texturaRect.y = 0; texturaRect.x = 0;
			}
			timer = SDL_GetTicks();
			cout << texturaRect.x << " " << texturaRect.y << endl;
		}
		tex->render(texturaRect, bat);		
	}	
	//GATO
	inline int getWeightCat() { return wCat_; };
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
};

