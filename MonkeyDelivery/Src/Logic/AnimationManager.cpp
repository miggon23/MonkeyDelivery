#include "AnimationManager.h"
#include "Game.h"
#include "../Utils/Timer.h"

AnimationManager* AnimationManager::sInstance = nullptr;

AnimationManager* AnimationManager::Instance(){
	return sInstance;
}
AnimationManager* AnimationManager::initialInstance(Game* game ) {
	if (sInstance == nullptr) {
		sInstance = new AnimationManager(game);
	}
	return sInstance;
}
void AnimationManager::getFrameImagePlayer(SDL_Rect player, SDL_Rect& texturaRect, Texture* tex, float& timer, LastDir newDir) {
	//Si la direccion cambia (da igual de que componente)
	if (lastDir.x != newDir.x || lastDir.y != newDir.y) {
		texturaRect.x = 0;
		lastDir = newDir;
		if (game_->getTimer()->TimeScale() - timer >= playerFrameSpeed) {
			texturaRect.x += 16;
			if (texturaRect.x >= playerLimit) {
				texturaRect.x = 0;
			}
			timer = game_->getTimer()->TimeScale();
		}
	}

	if (playerState_ == Running)
	{
		//las x
		switch (newDir.x)
		{
			//Derecha
			case 1: texturaRect.y = 54; break;
			//Izquierda
			case -1: texturaRect.y = 36; break;
			default: break;
		}

		//las y
		switch (newDir.y)
		{
			//Abajo
			case 1: texturaRect.y = 0; break;
			//Arriba
			case -1: texturaRect.y = 72; break;
			default: break;
		}

		tex->render(texturaRect, player);

		if (game_->getTimer()->TimeScale() - timer >= playerFrameSpeed) {
			texturaRect.x += 16;
			if (texturaRect.x >= playerLimit) {
				texturaRect.x = 0;
			}
			timer = game_->getTimer()->TimeScale();
		}
	}
	else if (playerState_ == Idle) {
		texturaRect.x = x1;
		if(isScared_)texturaRect.y = 198;
		else if (isTired_) texturaRect.y = 108;
		else texturaRect.y = 18;
		tex->render(texturaRect, player);
		if (game_->getTimer()->TimeScale() - timer >= playerFrameSpeed) {
			x1 += 16;
			if (texturaRect.x >= playerLimit - wPlayer_) {
				texturaRect.x = 0;
				x1 = 0;
			}
			timer = game_->getTimer()->TimeScale();
		}
		isTired_ = false;
		isScared_ = false;
	}
	else if (playerState_ == GoToSleep) {

		//las x
		switch (newDir.x)
		{
			//Derecha
			case 1: texturaRect.y = 144; break;
			//Izquierda
			case -1: texturaRect.y = 126; break;
			default: break;
		}
		//las y
		switch (newDir.y)
		{
			//Abajo
			case 1: texturaRect.y = 90; break;
			//Arriba
			case -1: texturaRect.y = 162; break;
			default: break;
		}

		texturaRect.x = x1;
		tex->render(texturaRect, player);

		if (game_->getTimer()->TimeScale() - timer >= playerFrameSpeed) {
			x1 += 16;
			if (texturaRect.x >= playerLimit - wPlayer_) {
				texturaRect.x = 0;
				x1 = 0;
			}
			timer = game_->getTimer()->TimeScale();
		}
	}
	else if (playerState_ == Scared) {
		//las x
		switch (newDir.x)
		{
			//Derecha
			case 1: texturaRect.y = 234; break;
			//Izquierda
			case -1: texturaRect.y = 216; break;
			default: break;
		}

		//las y
		switch (newDir.y)
		{
			//Abajo
			case 1: texturaRect.y = 180; break;
			//Arriba
			case -1: texturaRect.y = 252; break;
			default: break;
		}

		texturaRect.x = x1;
		tex->render(texturaRect, player);

		if (game_->getTimer()->TimeScale() - timer >= playerFrameSpeed) {
			if (game_->getTimer()->TimeScale() - timer >= playerFrameSpeed) {
				x1 += 16;
				if (texturaRect.x >= playerLimit - wPlayer_) {
					texturaRect.x = 0;
					x1 = 0;
				}
				timer = game_->getTimer()->TimeScale();
			}
		}
	}
	if (playerState_ == Sleeping)
	{
		texturaRect.x = x2;
		texturaRect.y = 270;
		tex->render(texturaRect, player);

		if (game_->getTimer()->TimeScale() - timer >= playerFrameSpeed) {
			x2 += 24;
			if (texturaRect.x >= 24) {
				texturaRect.x = 0;
				x2 = 0;
			}
			timer = game_->getTimer()->TimeScale();
		}
	}
}

void AnimationManager::getFrameImage(SDL_Rect rect, SDL_Rect& texturaRect, Texture* tex, float& timer, SDL_RendererFlip flip,
	int w, int h, int maxX, int maxY, int time) {
	if (game_->getTimer()->TimeScale() - timer >= time) {
		texturaRect.x += w;
		if (texturaRect.y >= maxY && texturaRect.x >= maxX) {
			texturaRect.y = 0; texturaRect.x = 0;
		}
		if (texturaRect.x >= maxX) {
			texturaRect.x = 0;
			texturaRect.y += h;
		}
		timer = game_->getTimer()->TimeScale();
	}
	tex->render(texturaRect, rect, 0, nullptr, flip);
}