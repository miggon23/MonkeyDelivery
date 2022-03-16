#pragma once
#include "InventoryObject.h"

class Game;

class Bike : public InventoryObject
{
private:
	bool active;
	double speedMult;
public:
	
	Bike(Texture* tex);

	bool useObject() override;
	inline void setBikeSpeedMultiplier(double speed) { speedMult = speed; };
	inline double getBikeSpeedMultiplier() { return speedMult; };
};

