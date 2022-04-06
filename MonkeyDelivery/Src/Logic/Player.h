#pragma once

#include "GameObject.h"
#include "energyLevel.h"
#include "FearLevel.h"
#include "Inventory.h"
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
	bool usingFlashLight = false;
	bool usingLantern = false;
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

	Texture* fadeTex_ = nullptr;

	int bedX_;
	int bedY_;

public:

	Player(Game* game, AnimationManager* animation);
	~Player();
	
	void update() override;
	void draw() override;

	// SLEEP
	void sleep(); //efecto de dormir
	void changeSleep(); //mirar si puede dormir
	void NoSleepText(); //si presionas la e pero no puedes dormir para que renderize el texto
	inline void bedPos(int x, int y) { bedX_ = x; bedY_ = y; }
	// ENERGY
	void drainEnergy(float amount) { energyLevel_->drain(amount); };
	inline void recoverEnergy(int amount) {};
	inline float getEnergy() { return energyLevel_->getEnergy(); };
	inline float getMaxEnergy() { return energyLevel_->getMaxEnergy(); };

	// FEAR
	inline void getScared(int amount) { fearLevel_->getScared(amount); };
	inline void recoverFear(int amount) {};

	// MOVEMENT
	void move(pair<double, double> speed);
	void move();
	void setIsRunning(bool run);
	inline void setVel(double x) { vel_ = x; };
	inline void resetVelocity() { setVel(INIT_VEL_); }; // Resetea la velocidad del jugador a la de por defecto (sin modificaciones)
	inline double getVel() { return vel_; };

	inline void setDirX(int x) { dirX_ = x; };
	inline void setDirY(int y) { dirY_ = y; };
	inline void setDir(int x, int y) { dirX_ = x; dirY_ = y; };

	inline MovState getMovState() { return movState_; };
	inline void setMovState(MovState m) { movState_ = m; };

	// ECONOMY
	bool moneyChange(int money);
	inline void addMoney(int amount) { money_ += amount; };
	void removeMoney(int amount);

	// INVENTORY
	inline void useObject(int index) { inventory_->useObject(index); };
	inline void setInventoryVisibility(bool visible) { inventoryVisibility = visible; };
	inline bool hasMissionObject() { return inventory_->hasMissionObject(); };
	inline void addMissionObject(InventoryObject* p) { inventory_->addMisionObject(p); };
	inline void removeMissionObject() { inventory_->removeMisionObject(); };
	inline bool inventoryFull() { return inventory_->inventoryFull(); };
	inline void addObjectToInventory(InventoryObject* p) { inventory_->addObject(p); };

	//DEVUELVE EL OBJECTO ACTIVADO POR EL JUGADOR
	inline string getActiveItemObject() {
		return inventory_->activeObject();
	};
	inline void selectObject(int index) {
		inventory_->selectObject(index);
	};
	inline void useSelectedObject() { inventory_->useSelectedObject(); };

	// LIGHTS
	const SDL_Rect lightZoneFL();
	const SDL_Rect lightZoneL();
	
	inline void changeFLState(bool f) {usingFlashLight = f;}
	inline void changeLState(bool f) { usingLantern = f;}

	inline bool isUsingFlashLight() { return usingFlashLight; }
	inline bool isUsingLantern() { return usingLantern; }

	inline void setOrientation(string orien) { orientation_ = orien; }
	inline string getOrientation() { return orientation_; }
	inline bool isAsleep() { return sleeping; }

	// FADEOUT
	void FadeOut(); // Realiza un fadeout sobre la pantalla
	void sendToBed(); // Establece la posición en la cama más cercana después del fadeout
};