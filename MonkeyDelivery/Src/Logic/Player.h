#include "GameObject.h"
#include "energyLevel.h"

class Game;

class Player: public GameObject {
private:
	float fear_;
	float walkingSpeed_;
	float runningSpeed_;
	//Mission activeMission_
	int money_;
	float fieldOfView_;

	// ENERGY BAR 
	int walkingEnergy_;
	energyLevel* energyLevel_ = nullptr;

public:
	Player(Game* game);
	~Player();

	void update() override;
	void move(pair<double, double> speed);
	void sleep();
	void getScared(int amount);
	void drainEnergy(int amount);
	void recoverEnergy(int amount);
	void recoverFear(int amount);
	void getMoney(int amount);
	void removeMoney(int amount);
	void draw() override;

};


