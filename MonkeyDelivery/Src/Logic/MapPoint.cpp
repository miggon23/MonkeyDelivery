#include "MAPPoint.h"

MAPPoint::MAPPoint(Game* game) :GameObject(game) {
	setTexture(mapPointerTexture);
	setDimension(100, 100);
};