#include "ShopState.h"
#include "../PauseCommand.h"
#include "../CommandExit.h"
#include "../ShopCommand.h"
#include "../../Logic/Shop.h"
#include <string>
ShopState::ShopState(Game* game) : State(game){
	registerCommands();

	panelTexture=game->getTexture(shop_UI_PanelShop);
	font_ = new Font("Images/fonts/Pixellari.ttf", 40);

	xObj = game->getWindowWidth() / 5;
	yObj = game->getWindowHeight() / 3;
	wObj = game->getWindowWidth() / 2.5;
	hObj = game->getWindowHeight() / 2;
	xOffset = game->getWindowWidth() / 10;
	yOffset = game->getWindowHeight() / 4;
	xText = game->getWindowWidth() / 2.65;
	yText = game->getWindowHeight() / 1.2;


	shop_ = game->getShop();
	shop_->actualice();
	maxSelected = shop_->getSize();
}

ShopState::~ShopState()
{
	
	panelTexture = nullptr;
	//delete shop_;
	shop_ = nullptr;
	delete font_;
	font_ = nullptr;
}


void ShopState::update()
{
}

void ShopState::draw()
{
	//renderizado del fondo
	
	SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(),(int)game->getWindowHeight() };
	panelTexture->render(rectPanel);
	std::cout << selected_ << std::endl;
	int i = 0;

	
	//pruebas
	//while (i < 4 && i < shop_->getSize())
	//{
	//	//shop_->objects[i]->getTexture()->render({ xOffset + xObj * i, yOffset, wObj, hObj });
	//	shop_->objects2[i].inventoryObject->getTexture()->render({ xOffset + xObj * shop_->objects2[i].positionRectX, yOffset, wObj, hObj });
	//	i++;
	//}	
	
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
	font_->render(game->getRenderer(), "Monedas: " + std::to_string(game->getMoney()), game->getWindowWidth() - 800, game->getWindowHeight() - 200, BLACK);
	//renderizado del texto
	if (shop_->objects.size()>selected_&&shop_->objects[selected_].stock > 0) {
		font_->render(game->getRenderer(), "Coste: " + std::to_string(shop_->objects[selected_].price), 600, game->getWindowHeight() - 200, BLACK);
	}
	else {
		font_->render(game->getRenderer(), " ", xText, yText, BLACK);
	}

	if (closeFailed_)
	{
		font_->render(game->getRenderer(), textError_, xText + 150, yText - 5, BLACK);
		if (SDL_GetTicks() > lastClicked_ + FAIL_TIMESHOWED) 
			closeFailed_ = false;
	}
	
}

void ShopState::next()
{
}

void ShopState::registerCommands()
{
	commandFactory->add(new PauseCommand());
	commandFactory->add(new CommandExit());
	commandFactory->add(new ShopCommand(this));
}

void ShopState::moveSelectedX(int to)
{
	//pruebas, sustituir 6 shop_->getSize()-1
	//if (selected_ == shop_->getSize() - 1 && to > 0)
	//	selected_ = 0;
	//else if (selected_ == 0 && to < 0)
	//	selected_ = shop_->getSize() - 1;
	//else
	//	selected_ += to;
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

		if(!shop_->buyObject(selected_, shop_->objects[selected_].price)) textError_ = "You already have bought this object";

		else if (shop_->inventoryFull(selected_))
			textError_ = "Inventory full";
		else 
			textError_ = "Not enough money";

		closeFailed_ = true;
	}
	else
	{
		closeFailed_ = false;
		sdlutils().soundEffects().at("buy").setVolume(game->getSoundEfectsVolume()*game->getGeneralVolume());
		sdlutils().soundEffects().at("buy").play(0, 1);
	}
}
