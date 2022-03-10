#include "Flashlight.h"
#include "Player.h"

Flashlight::Flashlight() : active(false)
{
}

bool Flashlight::useObject() {
	if (!active) {
		cout << " Hola linternita";
	}
	else {
		cout << "Adios linternita";
	}
	cout << endl;
	active = !active;
	return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
}

SDL_Rect Flashlight::lightZone()
{
	return {player_->getX(),player_->getY(),
		    player_->getWidth()*2,player_->getHeight()*2};
}
