#pragma once

#include "InventoryObject.h"

class Skates : public InventoryObject
{
private:
	bool active;
	double speedMult;
public:
	Skates(Texture* tex, Game* game);

	bool useObject() override;
	inline void setBikeSkatesMultiplier(double speed) { speedMult = speed; };
	inline double getBikeSkatesMultiplier() { return speedMult; };
};