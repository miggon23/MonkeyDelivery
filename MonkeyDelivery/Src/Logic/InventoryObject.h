#pragma once

#include "../View/Texture.h"

class Game;
class Player;
enum TypeObjectInventory {
	BOTAS, //
	CONSUMIBLES, //
	PICO, //
	LINTERNA,
	PAQUETE, //
	SINASIGNAR
};
class InventoryObject
{
private:
	Texture* myTexture_ = nullptr;

protected:
	Player* player_ = nullptr;
	Game* game_ = nullptr;
	bool isConsumable_ = false;	
	bool active = false;
	//TEMPORAL
	string typeObjectAux = "InventoryObject";
	TypeObjectInventory typeObject;
public:
	
	//InventoryObject() {};
	InventoryObject(Texture* tex, Game* game) : myTexture_(tex), game_(game) { typeObject = SINASIGNAR; };
	~InventoryObject();
	
	virtual bool useObject();
	void attachPlayer(Player* player);

	void setMyTexture(Texture* imgRoute);
	inline Texture* getTexture() { return myTexture_; };

	inline bool isConsumable() { return isConsumable_; };
	
	//inline bool hasTexture() { return myTexture_ != nullptr; };

	//TEMPORAL
	/*inline string getTypeObject() { return typeObjectAux; };
	inline void setTypeObject(string x) { typeObjectAux = x; };*/
	inline void setTypeObject(TypeObjectInventory x) { typeObject= x; };
	inline bool getActive() { return active; };
	
};