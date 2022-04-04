#include "MapPoint.h"

MapPoint::MapPoint(Game* game):GameObject(game){
	setTexture(mapPointerTexture);
	setDimension(100,100);
}

MapPoint::~MapPoint(){
	delete texture;
}

void MapPoint::update(){
}

void MapPoint::draw(){
	texture->render(getCollider());
}


