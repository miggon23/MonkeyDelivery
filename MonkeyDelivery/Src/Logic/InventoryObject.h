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

public:
	//InventoryObject() {};
	InventoryObject(Texture* tex) : myTexture_(tex) {};
	~InventoryObject();

	virtual bool useObject();
	void attachPlayer(Player* player);

	void setMyTexture(Texture* imgRoute);
	inline Texture* getTexture() { return myTexture_; };

	inline bool isConsumable() { return isConsumable_; };
	//inline bool hasTexture() { return myTexture_ != nullptr; };
};

