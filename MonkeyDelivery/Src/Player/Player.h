#pragma once

#include "../Logic/GameObject.h"
#include "energyLevel.h"
#include "FearLevel.h"
#include "../Logic/Inventory.h"
#include "../Logic/InventoryObject.h"
#include "../sdlutils/SDLUtils.h"

class Game;
class Inventory;
class AnimationManager;

enum Directions {
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3
};
enum PowerUps {
	energyDrink,
	boots,
	banana,
	cofee
};
class PowerUpsManager;
class Player : public GameObject {

	friend class UI_Info;
	enum MovState { WALKING, RUNNING, RIDING };
	
private:

	Inventory* inventory_ = nullptr;
	PowerUpsManager* powerUpsManager = nullptr;
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
	uint lastUpdate; // para el movimiento
	MovState movState_;
	//Velocidad base (sin modificaciones que mantiene el player)
	double INIT_VEL_;
	bool isRunning = false;
	double fear_;
	double walkingSpeedFactor_; //A esto se le multiplica la velocidad actual
	double runningSpeedFactor_; // A esto se le multiplica la velocidad actual
	//Velocidad actual del jugador
	double vel_;
	double dirX_ = 0; // 1, 0 o -1
	int dirY_ = 0; // 1, 0 o -1

	// Direcciones en las que no se puede mover por colisiones
	bool topCollision = false;
	bool bottomCollision = false;
	bool leftCollision = false;
	bool rightCollision = false;

#pragma endregion

#pragma region Mission activeMission	
	int money_;
	double fieldOfView_;
#pragma endregion

#pragma region Energy
	double walkingEnergy_;
	double runningEnergy_;
	double decreasingEnergyLevel_;
	energyLevel* energyLevel_ = nullptr;
	FearLevel* fearLevel_ = nullptr;
	//FearBar* fearBar_ = nullptr;
#pragma endregion

#pragma region Animations	
	AnimationManager* animationManager;
	SDL_Rect textureRect;
	float timerAnimation;
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
	void drainEnergy(double amount) { energyLevel_->drain(amount); };
	inline void recoverEnergy(int amount) {};
	inline double getEnergy() { return energyLevel_->getEnergy(); };
	inline double getMaxEnergy() { return energyLevel_->getMaxEnergy(); };
	inline void setStopSpending(bool set) { energyLevel_->setStopSpending(set); };

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
	inline void useObject(int index) { inventory_->useObject(index);};
	void initPowerUp(PowerUps x);
	inline void setInventoryVisibility(bool visible) { inventoryVisibility = visible; };
	inline bool hasMissionObject() { return inventory_->hasMissionObject(); };
	inline void addMissionObject(InventoryObject* p) { inventory_->addMisionObject(p); };
	inline void removeMissionObject() { inventory_->removeMisionObject(); };
	//inline bool inventoryFull() { return inventory_->inventoryFull(); };
	inline bool inventoryFull(InventoryObject* x) { return inventory_->inventoryFull(x); };
	inline void addObjectToInventory(InventoryObject* p) { inventory_->addObject(p); };
	
	inline void selectObject(int index) {
		inventory_->selectObject(index);
	};
	inline void mouseWheelSelectedObject(int index) {
		inventory_->changeSelectedObject(index);
	}
	inline void useSelectedObject() { 
		inventory_->useSelectedObject(); 
	};

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
	void sendToBed(); // Establece la posici�n en la cama m�s cercana despu�s del fadeout

	// COLLISIONS
	void onCollision(int dir);
	void onCollisionExit();

	// PICKAXE
	void addPickaxe(int level);
};