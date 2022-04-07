#pragma once

#include "../View/Texture.h"

class Game;
class Player;

class InventoryObject
{
private:
	Texture* myTexture_ = nullptr;

protected:
	Player* player_ = nullptr;
	Game* game_ = nullptr;
	bool isConsumable_ = false;	
	//TEMPORAL
	string typeObject = "InventoryObject";
public:
	
	//InventoryObject() {};
	InventoryObject(Texture* tex, Game* game) : myTexture_(tex),game_(game) {};
	~InventoryObject();

	virtual bool useObject();
	void attachPlayer(Player* player);

	void setMyTexture(Texture* imgRoute);
	inline Texture* getTexture() { return myTexture_; };

	inline bool isConsumable() { return isConsumable_; };
	
	//inline bool hasTexture() { return myTexture_ != nullptr; };

	//TEMPORAL
	inline string getTypeObject() { return typeObject; };
	inline void setTypeObject(string x) { typeObject = x; };
};