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
	inline ~AnimationManager() {};
	inline void getFrameImagePlayer(SDL_Rect player, Texture* tex) {
		
	}
	//MURCIELAGO
	inline int getWeightBat() { return wBat_; };
	inline int getHeightBat() { return hBat_; };
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
			cout << texturaRect.x << " " << texturaRect.y << endl;
		}
		tex->render(texturaRect, cat);
	}
};

