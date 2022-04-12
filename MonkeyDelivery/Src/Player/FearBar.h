#include "../Logic/GameObject.h"

class Game;

class FearBar : public GameObject {
private:
	
	float place_;
	float fear_;
	float maxFear_;

public:
	FearBar(Game* game);
	~FearBar() { };

	void update() override {};
	bool getScared(int amount);
	void draw() override;

	inline float percentFear() { return (fear_ / maxFear_) * 100; };
};


