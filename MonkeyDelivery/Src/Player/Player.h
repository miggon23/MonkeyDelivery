#pragma once

#include "../Logic/GameObject.h"
#include "energyLevel.h"
#include "FearLevel.h"
#include "playerHUD.h"
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
	monkeycola,
	repelente
};

class PowerUpsManager;
class Player : public GameObject {

	friend class UI_Info;
	enum MovState { WALKING, RUNNING, RIDING };
	
private:

	PowerUpsManager* powerUpsManager = nullptr;
	
	VirtualTimer timer;

	bool isTalking_ = false; // determina si el player está con un diálogo abierto
							 // para bloquear su movimiento y acciones
	bool isInTutorial_ = false;

	//INVENTARIO
	Inventory* inventory_ = nullptr;
	bool inventoryVisibility;

	//DORMIR
	bool sleeping = false;
	bool boolrenderSleepText = false;
	int timerSleepText;

	//MOVIMIENTO
	uint lastUpdate; // para el movimiento
	MovState movState_;
	//Velocidad base (sin modificaciones que mantiene el player)
	double INIT_VEL_;
	bool isRunning = false;
	double walkingSpeedFactor_; //A esto se le multiplica la velocidad actual
	double runningSpeedFactor_; // A esto se le multiplica la velocidad actual
	bool isStopped_;

	//Velocidad actual del jugador
	double vel_;
	double dirX_ = 0;		// 1, 0 o -1
	int dirY_ = 0;			// 1, 0 o -1
	bool reducedSpeed_;		//Cuanto disminuye la velocidad
	int reduceFactor_;		//Indica si la velocidad ha sido reducida, para que no se reduzca constantemente
	double previusVel_;		//Velocidad antes de reducirla al quedarse sin energia

	// Direcciones en las que no se puede mover por colisiones
	bool topCollision = false;
	bool bottomCollision = false;
	bool leftCollision = false;
	bool rightCollision = false;

	//MIEDO
	double fear_;
	double fearBonusFactor = 1;

	//MISION ACTIVA
	int money_;
	double fieldOfView_;

	//ENERGIA
	int maxEnergyPercent_;		//Limite de energia que se rellena al estar parado
	double reduceEnergyFactor_; //Cantidad en la que aumenta la energia cada frame al estar parado
	double walkingEnergy_;
	double runningEnergy_;
	double decreasingEnergyLevel_;
	energyLevel* energyLevel_ = nullptr;
	FearLevel* fearLevel_ = nullptr;
	playerHUD* playerHUD_ = nullptr;

	//ANIMACIONES
	AnimationManager* animationManager;
	SDL_Rect textureRect;
	float timerAnimation;

	//LINTERNAS
	string orientation_;
	Texture* flashlightTex_;
	Texture* lanternTex_;
	bool usingFlashLight = false;
	bool usingLantern = false;
	bool flashLOn = false;
	bool lanternOn = false;

	//FADE OUT
	Texture* fadeTex_ = nullptr;
	int bedX_;
	int bedY_;
	bool fade = false;
	int alpha = SDL_ALPHA_TRANSPARENT;

	//INFORMACION 
	Vector2D<int> posBeforeSleep;

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
	inline void drainEnergy(double amount) { energyLevel_->drain(amount); };
	inline double getEnergy() { return energyLevel_->getEnergy(); };
	inline double getMaxEnergy() { return energyLevel_->getMaxEnergy(); };
	

	// FEAR
	inline void getScared(double amount) { fearLevel_->getScared(amount / fearBonusFactor); }; //Por defecto fearBonusFactor = 1
	inline void setFearBonusFactor(double d = 1) { fearBonusFactor = d; };
	inline void recoverFear(double amount) { fearLevel_->getScared(-amount); };
	inline double getFear() { return fearLevel_->getFear(); };
	inline double getFearPercent() { return fearLevel_->percentFear(); };

	// MOVEMENT
	void move();
	void setIsRunning(bool run);
	inline void setVel(double x) { vel_ = x; };
	inline void resetVelocity() { setVel(INIT_VEL_); }; // Resetea la velocidad del jugador a la de por defecto (sin modificaciones)
	inline double getVel() { return vel_; };
	inline int getMoney() { return money_; };
	inline void setDirX(int x) { dirX_ = x; };
	inline void setDirY(int y) { dirY_ = y; };
	inline void setDir(int x, int y) { dirX_ = x; dirY_ = y; };
	inline MovState getMovState() { return movState_; };
	inline void setMovState(MovState m) { movState_ = m; };
	inline void savePosBeforeSleep() { posBeforeSleep.setX(getX()); posBeforeSleep.setY(getY()); };

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

	inline void changeTalking(bool a) { isTalking_ = a; };
	inline bool isTalking() { return isTalking_; };
	
	inline void changeTutorial(bool a) { isInTutorial_ = a; };
	inline bool isInTutorial() { return isInTutorial_; };

};