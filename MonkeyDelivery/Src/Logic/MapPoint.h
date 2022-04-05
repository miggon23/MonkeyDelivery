#pragma once
#include "GameObject.h"
class MAPPoint :public GameObject {
public:
	MAPPoint(Game* game);
	~MAPPoint()=default;
	void update() override {
	}	
};