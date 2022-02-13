#include "GameObject.h"
class Game;

class Player: public GameObject {
private:
	float energy_;
	float fear_;
	float walkingSpeed_;
	float runningSpeed_;
	//Mission activeMission_
	int money_;
	float fieldOfView_;
public:
	Player(Game* game);

	void update() override;
	void move(pair<double, double> speed);
	void sleep();
	void getScared(int amount);
	void drainEnergy(int amount);
	void recoverEnergy(int amount);
	void recoverFear(int amount);

};


