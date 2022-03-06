#pragma once

#include "../View/Texture.h"

class Game;
class Player;

class InventoryObject
{
private:
	Texture* myTexture_;

protected:
	Player* player_ = nullptr;

public:
	InventoryObject() {};
	InventoryObject(Texture* tex) : myTexture_(tex) {};
	~InventoryObject();

	virtual bool useObject();
	void attachPlayer(Player* player);

	void setMyTexture(Texture* imgRoute);
	inline Texture* getTexture() { return myTexture_; };
};

