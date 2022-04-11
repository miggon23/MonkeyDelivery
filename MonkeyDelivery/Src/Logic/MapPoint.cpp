#include "MAPPoint.h"

MAPPoint::MAPPoint(Game* game) :GameObject(game) {
	setTexture(mapMarker);
	setDimension(100, 100);
};