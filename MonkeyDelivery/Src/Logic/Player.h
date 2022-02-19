#include "GameObject.h"
#include "energyLevel.h"

class Game;

class Player: public GameObject {
private:

	bool isRunning=false;
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
	void sleep();
	void getScared(int amount);
	void drainEnergy(int amount);
	void recoverEnergy(int amount);
	void recoverFear(int amount);
	void draw() override;

	//Movement
	void move(pair<double, double> speed);
	inline void setIsRunning(bool run) { isRunning = run; };

	//economy
	bool moneyChange(int money);
	void getMoney(int amount);
	void removeMoney(int amount);
};


