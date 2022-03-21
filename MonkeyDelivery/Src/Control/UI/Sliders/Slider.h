#pragma once
#include "../../../Logic/GameObject.h"
class Slider: public GameObject
{
public:
	Slider();
	~Slider();
	void draw() override;	
	void update() override;
private:
	//Necesitamos una parte de panel y la otra parte clicable

};

