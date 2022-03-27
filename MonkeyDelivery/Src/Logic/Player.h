#pragma once

#include "GameObject.h"
#include "energyLevel.h"
#include "FearLevel.h";

#include "InventoryObject.h"

#include "../sdlutils/SDLUtils.h"

class Game;
class Inventory;
class AnimationManager;

class Player : public GameObject {

	friend class UI_Info;
	enum MovState { WALKING, RUNNING, RIDING };

private:
	Inventory* inventory_ = nullptr;
	bool inventoryVisibility;
	bool fade = false;
	int alpha = SDL_ALPHA_TRANSPARENT;
	VirtualTimer timer;

#pragma region Sleep
	bool sleeping = false;
	bool boolrenderSleepText = false;
	int timerSleepText;
	bool flashLOn = false;
	bool lanternOn = false;
#pragma endregion

#pragma region Movement/Fear
	MovState movState_;
	//Velocidad base (sin modificaciones que mantiene el player)
	double INIT_VEL_;
	bool isRunning = false;
	float fear_;
	float walkingSpeedFactor_; //A esto se le multiplica la velocidad actual
	float runningSpeedFactor_; // A esto se le multiplica la velocidad actual
	//Velocidad actual del jugador
	double vel_;
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
	float decreasingEnergyLevel_;
	energyLevel* energyLevel_ = nullptr;
	FearLevel* fearLevel_ = nullptr;
#pragma endregion

#pragma region Animations	
	AnimationManager* animationManager;
	SDL_Rect textureRect;
	int timerAnimation;
#pragma endregion	

	//orientacion para la linterna
	string orientation_;
	Texture* flashlightTex_;
	Texture* lanternTex_;

	Texture* fadeTex_;

public:

	Player(Game* game, AnimationManager* animation);
	~Player();
	
	void update() override;
	void draw() override;

#pragma region Sleep
	void sleep();//efecto de dormir
	void changeSleep();//mirar si puede dormir
	void NoSleepText();//si presionas la e pero no puedes dormir para que renderize el texto
#pragma endregion

#pragma region Energy
	void drainEnergy(float amount);
	void recoverEnergy(int amount);
	inline float getEnergy() { return energyLevel_->getEnergy(); };
	inline float getMaxEnergy() { return energyLevel_->getMaxEnergy(); };
#pragma endregion

#pragma region Fear
	void getScared(int amount);
	void recoverFear(int amount);
#pragma endregion

#pragma region Movement
	void move(pair<double, double> speed);
	void move();
	void setIsRunning(bool run);
	inline void setVel(double x) { vel_ = x; };
	void resetVelocity();
	inline double getVel() { return vel_; };

	inline void setDirX(int x) { dirX_ = x; };
	inline void setDirY(int y) { dirY_ = y; };
	inline void setDir(int x, int y) { dirX_ = x; dirY_ = y; };

	inline MovState getMovState() { return movState_; };
	inline void setMovState(MovState m) { movState_ = m; };

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
	//linterna
	const SDL_Rect lightZoneFL();
	const SDL_Rect lightZoneL();
	bool usingFlashLight = false;
	bool usingLantern = false;
	void changeFLState(bool f) {
		usingFlashLight = f;
	}
	void changeLState(bool f) {
		usingLantern = f;
	}
	inline void setOrientation(string orien) { orientation_ = orien; }
	inline string getOrientation() { return orientation_; }
	inline bool isAsleep() { return sleeping; }

	// Fadeout
	void FadeOut(); // Realiza un fadeout sobre la pantalla
	void sendToBed(); // Establece la posición en la cama más cercana después del fadeout
};


