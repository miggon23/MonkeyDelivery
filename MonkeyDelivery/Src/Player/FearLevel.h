#include "../Logic/GameObject.h"
class Game;

class FearLevel: public GameObject {
private:
	
	float place_;
	float fear_;
	float maxFear_;


public:
	FearLevel(Game* game);
	~FearLevel() { };

	void update() override {};
	bool getScared(int amount);
	void resetFear();
	void draw() override;

	inline float percentFear() { return (fear_ / maxFear_) * 100; };
};