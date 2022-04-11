#include "Target.h"
#include "MissionsPanel.h"
#include "Player.h"
#include "Game.h"

Target::Target(MissionsPanel* mp, Game* g) : GameObject(g, true), missionsPanel_(mp), myTexture_(nullptr)
{
	active_ = false;

	setDimension(1, 1);
	setPosition(0, 0);

}

Target::Target(MissionsPanel* mp, Game* g, string texture) : GameObject(g), missionsPanel_(mp)
{
	active_ = false;

	setDimension(1, 1);
	setPosition(0, 0);

	string route = "../Images/NPCs/" + texture + ".png";
	myTexture_ = new Texture(g->getRenderer(), route);
}

Target::~Target()
{
	missionsPanel_ = nullptr;
	delete myTexture_;
}

void Target::onPlayerInteraction(Player* player)
{
	if (active_) {

		if (player->hasMissionObject()) {

			game->newDialogue(textPath_);

			player->removeMissionObject();
			missionsPanel_->onMissionCompleted();
		}
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
	delete myTexture_;
	string route = "../Images/NPCs/" + tex + ".png";
	myTexture_ = new Texture(game->getRenderer(), route);
}