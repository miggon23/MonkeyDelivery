#pragma once
#include "../Logic/InventoryObject.h"

class Bike : public InventoryObject
{
private:
	double speedMult;
public:
	
	Bike(Texture* tex, Game* game,Player* player);

	bool useObject() override;
	inline void setBikeSpeedMultiplier(double speed) { speedMult = speed; };
	void setCorrectTexture() override;
	inline double getBikeSpeedMultiplier() { return speedMult; };
};