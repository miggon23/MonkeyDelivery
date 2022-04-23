#pragma once

#include "../View/Texture.h"

class Game;
class Player;
enum TypeObjectInventory {
	BOOTS, //
	CONSUMABLES, //
	PICKAXE, //
	LANTERN,
	PACKAGE, //
	UNSIGNED
}; 
class InventoryObject{
private:
	Texture* myTexture_ = nullptr;

protected:
	Player* player_ = nullptr;
	Game* game_ = nullptr;
	bool isConsumable_ = false;	
	bool active = false;
	TypeObjectInventory typeObject;
public:
	
	//InventoryObject() {};
	InventoryObject(Texture* tex, Game* game,Player* player);
	~InventoryObject();
	
	virtual bool useObject();
	void attachPlayer(Player* player);

	void setMyTexture(Texture* imgRoute);
	inline Texture* getTexture() { return myTexture_; };

	inline bool isConsumable() { return isConsumable_; };

	inline void setTypeObject(TypeObjectInventory x) { typeObject= x; };
	inline TypeObjectInventory getTypeObject() { return typeObject; }
	inline bool getActive() { return active; };
	
};