#include "GameObject.h"
class Game;

class energyLevel: public GameObject {
private:
	
	int place_;

public:
	energyLevel(Game* game);
	~energyLevel() {};

	void update() override {};
	void changeWidth(int change);
	void draw() override;

	

};


