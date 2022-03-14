#pragma once

#include "GameObject.h"
#include "energyLevel.h"
#include "FearLevel.h";

#include "InventoryObject.h"

class Game;
class Inventory;
class AnimationManager;

class Player : public GameObject {

	friend class UI_Info;

private:
	Inventory* inventory_ = nullptr;
	bool inventoryVisibility;
	bool fade = true;
	int alpha = SDL_ALPHA_TRANSPARENT;

#pragma region Sleep
	bool sleeping = false;
	bool boolrenderSleepText = false;
	int timerSleepText;
#pragma endregion

#pragma region Movement/Fear
	const double INIT_VEL = 3.0; //Velocidad base (sin modificaciones que mantiene el player
	bool isRunning = false;
	float fear_;
	float walkingSpeed_;
	float runningSpeed_;
	double velX_ = 0; //velocidad actual del jugador
	double velY_ = 0;
	int dirX_ = 0; // 1, 0 o -1
	int dirY_ = 0; // 1, 0 o -1
#pragma endregion

#pragma region Mission activeMission	
	int money_;
	float fieldOfView_;
#pragma endregion

#pragma region Energy
	float walkingEnergy_;
	float runningEnergy_;
	energyLevel* energyLevel_ = nullptr;
	FearLevel* fearLevel_ = nullptr;
#pragma endregion

#pragma region Animations	
	AnimationManager* animationManager;
	SDL_Rect textureRect;
	int timerAnimation;
#pragma endregion	

public:

	Player(Game* game,AnimationManager* animation);
	~Player();

	void update() override;
	void draw() override;

#pragma region Sleep
	void sleep();//efecto de dormir
	void changeSleep();//mirar si puede dormir
	void NoSleepText();//si presionas la e pero no puedes dormir para que renderize el texto
	void FadeOut();
#pragma endregion

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
	void move();
	inline void setIsRunning(bool run) { isRunning = run; std::cout << "RUNNING CHANGED TO: " << isRunning << endl; };
	inline void setVelX(double x) { velX_ = x; };
	inline void setVelY(double y) { velY_ = y; };
	inline void setVel(double x, double y) { velX_ = x; velY_ = y; };
	void resetVelocity();
	inline double getVelX() { return velX_; };
	inline double getVelY() { return velY_; };

	inline void setDirX(int x) { dirX_ = x; };
	inline void setDirY(int y) { dirY_ = y; };
	inline void setDir(int x, int y) { dirX_ = x; dirY_ = y; };

#pragma endregion

#pragma region economy
	bool moneyChange(int money);
	void getMoney(int amount);
	void removeMoney(int amount);
#pragma endregion

#pragma region inventory
	void useObject(int index);
	inline void setInventoryVisibility(bool visible) { inventoryVisibility = visible; };
	bool hasMissionObject();
	void addMissionObject(InventoryObject* p);
	void removeMissionObject();

	bool inventoryFull();
	void addObjectToInventory(InventoryObject* p);
#pragma endregion
};


