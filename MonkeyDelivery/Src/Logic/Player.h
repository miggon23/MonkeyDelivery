#include "GameObject.h"
#include "energyLevel.h"
class Game;
enum Animations { QUIETO, CORRER };//EN PROCESO <NO TOCAR>

class Player: public GameObject {

	friend class UI_Info;

private:
	
#pragma region Movement/Fear
	bool isRunning = false;
	float fear_;
	float walkingSpeed_;
	float runningSpeed_;
#pragma endregion

#pragma region Mission activeMission	
	int money_;
	float fieldOfView_;
#pragma endregion

#pragma region Energy
	float walkingEnergy_;
	energyLevel* energyLevel_ = nullptr;
#pragma endregion

#pragma region Animations	
	Animations animations;
	int indicatorTexture;
#pragma endregion	

public:
	
	Player(Game* game);
	~Player();

	void update() override;
	void draw() override;
	void sleep();

#pragma region Energy
	void drainEnergy(float amount);
	void recoverEnergy(int amount);
#pragma endregion

#pragma region Fear
	void getScared(int amount);
	void recoverFear(int amount);
#pragma endregion

#pragma region Movement
	void move(pair<double, double> speed);
	inline void setIsRunning(bool run) { isRunning = run; std::cout << "RUNNING CHANGED TO: " << isRunning << endl; };
#pragma endregion

#pragma region economy
	bool moneyChange(int money);
	void getMoney(int amount);
	void removeMoney(int amount);
#pragma endregion

};


