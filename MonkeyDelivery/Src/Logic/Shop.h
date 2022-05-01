#pragma once
#include <vector>

class Player;
class InventoryObject;
class Inventory;
class Game;
using namespace std;
struct elementShop{
	InventoryObject* inventoryObject;
	int positionRectX;
	int positionRectY;
	int stock;
	int price;
};
class Shop
{
friend class ShopState;

private:	
	vector <elementShop> objects;
	Player* player;
	Game* game;
	
public:

	Shop(Player* player, Game* game);
	~Shop();

	void actualice();
	void clearElements();
	void addElements(int level);
	bool buyObject(int id, int price);
	bool inventoryFull(int selected); 
	int getSize() { return (int)objects.size(); }
	void CreateNewObject(InventoryObject* O);
};