#pragma once
class Player;
class PowerUpsManager{
	Player* player_;
public:
	PowerUpsManager(Player* player);
	~PowerUpsManager();
	void update();
};

