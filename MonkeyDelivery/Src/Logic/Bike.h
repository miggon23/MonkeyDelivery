#pragma once
#include "InventoryObject.h"

class Bike : public InventoryObject
{
private:
	double speedMult;
public:
	
	Bike(Texture* tex, Game* game);

	bool useObject() override;
	inline void setBikeSpeedMultiplier(double speed) { speedMult = speed; };
	inline double getBikeSpeedMultiplier() { return speedMult; };
};