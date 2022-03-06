#include "Target.h"
#include "MissionsPanel.h"
#include "Player.h"
#include "Game.h"

Target::Target(MissionsPanel* mp, Game* g) : GameObject(g), missionsPanel_(mp)
{
	active_ = false;

	setDimension(120, 150);
	setPosition(500, 80);
	//setTexture(tucanTexture);

}

Target::Target(MissionsPanel* mp, Game* g, string texture) : GameObject(g), missionsPanel_(mp)
{
	active_ = false;

	setDimension(120, 150);
	setPosition(500, 80);

	string route = "../Images/animals/" + texture + ".png";
	myTexture_ = new Texture(g->getRenderer(), route);
}

Target::~Target()
{
	delete myTexture_;
}

void Target::onPlayerInteraction(Player* player)
{
	/*if (player->tieneElObjeto()) {

	}*/
	if (active_) {

		missionsPanel_->onMissionCompleted();
	}
}

void Target::update()
{
}

void Target::draw() {
	if (active_) {
		//drawTexture(texture);
		SDL_Rect rect = {getPosition().getX(), getPosition().getY(), getWidth(), getHeight()};
		myTexture_->render(rect);
	}
}

void Target::setTexture(string tex)
{
	string route = "../Images/animals/" + tex + ".png";
	myTexture_ = new Texture(game->getRenderer(), route);
}
