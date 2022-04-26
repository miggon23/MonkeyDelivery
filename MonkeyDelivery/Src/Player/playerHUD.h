#include "../Logic/GameObject.h"
class Game;

class playerHUD: public GameObject {
private:
	
public:
	playerHUD(Game* game);
	~playerHUD() { };

	void update() override {};
	void draw() override;
};