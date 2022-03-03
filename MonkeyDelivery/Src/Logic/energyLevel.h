#include "GameObject.h"
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
	void draw() override;
	inline float percentEnergy() { return (energy_ / maxEnergy_) * 100; };
};


