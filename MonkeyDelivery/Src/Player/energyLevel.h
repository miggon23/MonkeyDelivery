#pragma once
#include "../Logic/GameObject.h"

class Game;

class energyLevel: public GameObject {
private:
	
	double place_;
	double energy_;
	double maxEnergy_;
	double scale_;

	int x, y, w, h;
public:
	energyLevel(Game* game);
	~energyLevel() { };

	void update() override {};
	bool drain(double energyDrained);
	void resetEnergy();
	void draw() override;

	inline double getEnergy() { return energy_; };
	inline double getMaxEnergy() { return maxEnergy_; };
	//porcentaje de enegia que tiene el personaje
	inline double percentEnergy() { return (energy_ / maxEnergy_) * 100; };
};