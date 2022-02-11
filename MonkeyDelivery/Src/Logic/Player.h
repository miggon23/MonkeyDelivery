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
	void Move(double speed);
	void Sleep();
	void GetScared(int amount);
	void DrainEnergy(int amount);
	void RecoverEnergy(int amount);
	void RecoverFear(int amount);

};


