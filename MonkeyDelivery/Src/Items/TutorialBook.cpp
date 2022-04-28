#include "../Logic/Game.h"

TutorialBook::TutorialBook(Game* game, int x, int y, int w, int h) : ColliderTile(game, Point2D<double>(x,y), w, h) {
	setTexture(worldObject_Tutorial);
	tutorialTexture_ = game->getTexture(UI_Controls);
	tutorialKeyTexture_ = game->getTexture(UI_ControlsKey);
	tutorialRect_ = {0, 0, (int)game->getWindowWidth(), (int)game->getWindowHeight() };
	tutorialKeyRect_ = {x + 25 , y - 40, 50, 50 };
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
	SDL_Rect a = tutorialKeyRect_;
	a.x -= (int)game->getCamera()->getCameraPosition().getX();
	a.y -= (int)game->getCamera()->getCameraPosition().getY();

	tutorialKeyTexture_->render(a);
	drawTexture(texture);
	if (showingImage_) {
		tutorialTexture_->render(tutorialRect_);
	}
}

bool TutorialBook::isInteractive() {
	return true;
}