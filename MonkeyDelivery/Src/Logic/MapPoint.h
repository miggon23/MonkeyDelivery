#pragma once
#include "GameObject.h"

class MapPoint :public GameObject {
public:	
	MapPoint(Game* game);
	~MapPoint();
	void update() override;
	void draw() override;
};