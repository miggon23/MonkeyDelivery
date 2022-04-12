#include "../Logic/GameObject.h"
class Game;

class energyLevel: public GameObject {
private:
	
	float place_;
	float energy_;
	float maxEnergy_;


public:
	energyLevel(Game* game);
	~energyLevel() { };

	void update() override {};
	bool drain(float energyDrained);
	void resetEnergy();
	void draw() override;

	inline float getEnergy() { return energy_; };
	inline float getMaxEnergy() { return maxEnergy_; };
	//porcentaje de enegia que tiene el personaje
	inline float percentEnergy() { return (energy_ / maxEnergy_) * 100; };
};