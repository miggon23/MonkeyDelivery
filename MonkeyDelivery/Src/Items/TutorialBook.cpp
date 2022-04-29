#include "../Logic/Game.h"

TutorialBook::TutorialBook(Game* game, int x, int y, int w, int h) : ColliderTile(game, Point2D<double>(x,y), w, h) {
	setTexture(worldObject_Tutorial);
	tutorialTexture_ = game->getTexture(UI_Controls);
	tutorialRect_ = {0, 0, (int)game->getWindowWidth(), (int)game->getWindowHeight() };
	tutorialSignRect_ = {x + 25 , y - 40, 68, 132 };
}

void TutorialBook::onPlayerInteraction(Player* player)
{
	isActive_ = false;
	isColliding_ = false;
	onPlayerCollisionExit();

	showingImage_ = !showingImage_;
	player->changeTutorial(showingImage_);
	
}

void TutorialBook::draw()
{
	SDL_Rect a = tutorialSignRect_;
	a.x -= (int)game->getCamera()->getCameraPosition().getX();
	a.y -= (int)game->getCamera()->getCameraPosition().getY();

	//drawTexture(texture);
	texture->render(a);
	if (showingImage_) {
		tutorialTexture_->render(tutorialRect_);
	}
}

bool TutorialBook::isInteractive() {
	return true;
}