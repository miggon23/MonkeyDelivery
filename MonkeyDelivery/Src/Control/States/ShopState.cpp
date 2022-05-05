#include "ShopState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../ShopCommand.h"
#include "../../Logic/Shop.h"
#include <string>

ShopState::ShopState(Game* game) : State(game){
	registerCommands();

	panelTexture=game->getTexture(shop_UI_PanelShop);
	controlsTexture = game->getTexture(shop_UI_Controls);
	coinTexture = game->getTexture(UI_Coin);

	font_ = new Font("Images/fonts/Pixellari.ttf", 40);

	xObj = game->getWindowWidth()/4.44;
	yObj = game->getWindowHeight()/1.95;
	wObj = (int)(game->getWindowWidth() / 2.5);
	hObj = (int)game->getWindowHeight() / 2;
	xOffset = (int)game->getWindowWidth() / 20;
	yOffset = (int)game->getWindowHeight() / 5;
	xText = (int)(game->getWindowWidth() / 2.65);
	yText = (int)(game->getWindowHeight() / 1.2);

	buttonsX_ = (int)(game->getWindowWidth() / 1.3);
	buttonsY_ = (int)(game->getWindowHeight() / 1.3);
	buttonsW_ = game->getWindowWidth()/5;
	buttonsH_ = game->getWindowHeight()/6;

	coinsX_ = (int)(game->getWindowWidth() / 2.25);
	coinsY_ = (int)(game->getWindowHeight() / 1.3);
	coinsW_ = (int)(game->getWindowWidth() / 35.0);
	double d = game->getWindowWidth() / game->getWindowHeight(); // para que tengan el mismo W y H
	coinsH_ = (int)(game->getWindowHeight() / 35.0 * d);

	shop_ = game->getShop();
	maxSelected = shop_->getSize();
}

ShopState::~ShopState()
{
	panelTexture = nullptr;
	shop_ = nullptr;
	delete font_;
	font_ = nullptr;
}

void ShopState::draw()
{
	//renderizado del fondo
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(),(int)game->getWindowHeight() };
	panelTexture->render(rectPanel);
	std::cout << selected_ << std::endl;
	int i = 0;

	//renderizado de los objetos	
	while (i < shop_->getSize())
	{
		
	/*	if (shop_->objects[i].stock > 0) {
			if (i>=4) {
				shop_->objects[i].inventoryObject->getTexture()->render(
					{ xOffset + xObj * (shop_->objects[i].positionRectX-4) - 50 * (i-4),(int)( yOffset *(shop_->objects[i].positionRectY +0.75)+20), wObj, hObj });
			}
			else {
				shop_->objects[i].inventoryObject->getTexture()->render(
					{ xOffset + xObj * shop_->objects[i].positionRectX - 50 * i, yOffset + (shop_->objects[i].positionRectY * 3), wObj, hObj });
			}*/

		if (shop_->objects[i].stock > 0) {
			if (i >= 4) {
				shop_->objects[i].inventoryObject->getTexture()->render(
					{ xOffset + (xObj *( i * - 4)) , yOffset , xObj, yObj });
			}
			else {
				shop_->objects[i].inventoryObject->getTexture()->render(
					{ xOffset + xObj * i, yOffset, xObj, yObj });
			}
		}
		i++;
	}

	//renderizado del objeto seleccionado
	if(selected_ < 4)
		rectPanel = { xOffset + xObj * selected_ , yOffset , xObj, yObj };
	else
		rectPanel = { xOffset + xObj * (selected_ - 4), yOffset + yObj, xObj, yObj };
	
	game->getTexture(shop_UI_Selector)->render(rectPanel);
	// current money
	font_->render(game->getRenderer(), "Monedas: " + std::to_string(game->getMoney()), (int)game->getWindowWidth()/1.75, (int)game->getWindowHeight()/1.3, BLACK);
	//renderizado del texto
	if (shop_->objects.size()>selected_&&shop_->objects[selected_].stock > 0) {
		font_->render(game->getRenderer(), "Coste: " + std::to_string(shop_->objects[selected_].price), (int)game->getWindowWidth()/3, (int)game->getWindowHeight()/1.3, BLACK);
	}
	else {
		font_->render(game->getRenderer(), " ", xText, yText, BLACK);
	}

	if (closeFailed_)
	{
		font_->render(game->getRenderer(), textError_, xText + 25, yText + 25, BLACK);
		if ((int)SDL_GetTicks() > lastClicked_ + FAIL_TIMESHOWED) 
			closeFailed_ = false;
	}

	// renderizado de los controles
	rectPanel = {buttonsX_, buttonsY_, buttonsW_, buttonsH_};
	controlsTexture->render(rectPanel);
	
	// renderizado del icono moneda
	rectPanel = { coinsX_, coinsY_, coinsW_, coinsH_ };
	coinTexture->render(rectPanel);

	rectPanel.x += coinsX_/2 + 75;
	coinTexture->render(rectPanel);
}

void ShopState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
	commandFactory->add(new ShopCommand(this));
}

void ShopState::moveSelectedX(int to)
{
	if (selected_ + to < maxSelected && selected_ + to >= 0)
		selected_ += to;	
}

void ShopState::moveSelectedY(int to)
{
	if (selected_+ maxSelected/2 * to < maxSelected && selected_+ maxSelected / 2 * to >= 0)
		selected_=selected_+ maxSelected / 2 *to ;
}

void ShopState::buySelected()
{
	
	if (shop_->getSize()>selected_&&!shop_->buyObject(selected_, shop_->objects[selected_].price))
	{
		lastClicked_ = SDL_GetTicks();
		if(shop_->objects[selected_].price>game->getPlayer()->getMoney())textError_ = "Not enough money";
		else if(!shop_->buyObject(selected_, shop_->objects[selected_].price)) textError_ = "Inventory full";
		///*else if (shop_->inventoryFull(selected_))
		//	textError_ = "Inventory full";
		//else 
		//	textError_ = "Not enough money";*/

		closeFailed_ = true;
	}
	else
	{
		closeFailed_ = false;
		sdlutils().soundEffects().at("buy").setVolume((int)(game->getSoundEfectsVolume()*game->getGeneralVolume()));
		sdlutils().soundEffects().at("buy").play(0, 1);
	}
}
