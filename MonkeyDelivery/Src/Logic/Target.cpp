#include "Target.h"
#include "MissionsPanel.h"
#include "../Player/Player.h"
#include "Game.h"

Target::Target(MissionsPanel* mp, Game* g) : GameObject(g, true), missionsPanel_(mp)
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
	this->texture = new Texture(g->getRenderer(), route);
}

Target::~Target()
{
	missionsPanel_ = nullptr;
	delete texture;
	texture = nullptr;
}

void Target::onPlayerInteraction(Player* player)
{
	if (active_) {

		if (player->hasMissionObject()) {

			game->newDialogue(textPath_);

			player->removeMissionObject();
			missionsPanel_->onMissionCompleted();
		}
		else {
			// activar un dialogo que diga que busques su paquete
		}
	}
}

void Target::update()
{
}

void Target::draw() {
	if (active_) {
		//drawTexture(texture);
		 SDL_Rect pos = getCollider();

        //Dibujamos respecto a la camara
        pos.x -= (int)game->getCamera()->getCameraPosition().getX();
        pos.y -= (int)game->getCamera()->getCameraPosition().getY();

        texture->render(pos);
	}
}

void Target::setTexture(string tex)
{	
	if (texture != nullptr)
		delete texture;
	string route = "./Images/NPCs/" + tex + ".png";
	texture = new Texture(game->getRenderer(), route);
}