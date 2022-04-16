#include "PlayerIcon.h"

PlayerIcon::PlayerIcon(Game* game) :GameObject(game) {
	setTexture(playerIconTex);
	setDimension(100, 100);
};