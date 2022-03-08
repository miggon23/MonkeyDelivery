#include "Player.h"
#include "Inventory.h"
#include "Bike.h"
#include "Game.h"
#include "SDL.h"


Player::Player(Game* game, AnimationManager* animation) :GameObject(game),animationManager(animation) {
	this->game = game;
	
	texture = nullptr;
	setTexture(monkeyspritesheet);

	//inicializacion de variables
	fear_ = 0;
	money_ = 0;
	/*walkingSpeed_ = 3;
	runningSpeed_ = 10;*/
	walkingEnergy_ = 0.5;
	runningEnergy_ = 1.0;

	resetVelocity(); //Se inicializa al valor de INIT_VEL_X e ..._Y

	setPosition(15, 100);
	setDimension(90, 100);

	energyLevel_ = new energyLevel(game);
	fearLevel_ = new FearLevel(game);
	inventory_ = new Inventory(this, game->getRenderer());
	inventory_->addObject(new Bike());
	setInventoryVisibility(true);
	textureRect = { 0,0,100,100};
	timerAnimation = SDL_GetTicks();
}

Player::~Player()
{
	delete energyLevel_;
	delete fearLevel_;
	delete inventory_;
	energyLevel_ = nullptr;
	fearLevel_ = nullptr;
	inventory_ = nullptr;
}

void Player::update()
{
	//move();
	//getScared(1);//pruebas
	if (sleeping)sleep();//si esta durmiendo
	else move();//si no esta durmiendo habilitanmos el movimiento
}

/// <summary>
/// Se le suma a la pos la x y la y del parametro
/// </summary>
/// <param name="speed"> La primera componente es la x y la segunda la y</param>
void Player::move(pair<double, double> speed)
{

	/*if (velX != 0 || velY != 0) {
		if (isRunning) { 
			setPosition(getX() + speed.first*2, getY() + speed.second*2); 
			drainEnergy(runningEnergy_);
		}
		else{
			setPosition(getX() + speed.first, getY() + speed.second);
			drainEnergy(walkingEnergy_);
		}
	}*/
	//cout << "POSICION PLAYER:" << getX() << "," << getY() << endl;
	//cout << "POSICION BARRA:" << energyLevel_->getX() << "," << energyLevel_->getY() << endl;
}

void Player::move()
{
	double speedX = velX_ * dirX_;
	double speedY = velY_ * dirY_;

	if (dirX_ != 0 || dirY_ != 0) {
		if (isRunning) { //Esto se puede implementar desde el runCommand, evitando que el jugador tenga muchos estados como el de corriendo
			speedX *= 2;
			speedY *= 2;
			drainEnergy(walkingEnergy_);
		}
		else
			drainEnergy(walkingEnergy_);
	}

	//HAY QUE NORMALIZAR EL VECTOR
	setPosition(getX() + speedX, getY() + speedY);
}

/// <summary>
/// Resetea la velocidad del jugador a la de por defecto (sin modificaciones)
/// </summary>
void Player::resetVelocity()
{
	setVel(INIT_VEL_X, INIT_VEL_Y);
}

void Player::sleep()
{	
	std::cout << "A MIMIR YA PUTO MONO" << endl;
	//cambio la textura
	//setTexture(monkeyEyesClosedTexture);
	draw();
	getScared(-1);
	drainEnergy(-1);
}
//cambiar la variable de dormir y establecer la textura
void Player::changeSleep()
{	
	if (energyLevel_->percentEnergy() <= 20.0||sleeping) {
		sleeping = !sleeping;
		//actulizo la textura
		if (sleeping) {
			//setTexture(monkeyEyesClosedTexture);
		}
		else {
			//setTexture(monkeyTexture);
		}
		draw();
	}
	else {
		boolrenderSleepText = true;
		timerSleepText = SDL_GetTicks();
	}
}

void Player::NoSleepText()
{
	int x = game->getWindowWidth() / 2 - 250;
	int y = game->getWindowHeight() / 2 - 50;
	//Textos q renderiza
	vector<string> texts = {
			"No Puedes Dormir "," ",
			"Tienes Mucha Energia"
	};

	game->renderText(texts, x, y, 20, 20);
	//si ya ha pasado el tiempo desactivo
	if (SDL_GetTicks() - timerSleepText >= 3000)boolrenderSleepText = false;
}

void Player::FadeOut()
{
	//SDL_Surface* s;
	/* Creating the surface. */
	//s = SDL_CreateRGBSurface(0, game->getWindowWidth(), game->getWindowHeight(), 32, 0, 0, 0, 0);
	//SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 0, 0));
	/*auto rect= SDL_Rect(0, game->getWindowHeight(), game->getWindowWeight(), game->getWindowHeight()
	auto x = Texture(rect);
	SDL_SetTextureAlphaMod(,50);*/

	/*setTexture(monkeyEyesClosedTexture);

	SDL_Rect screenRectangle = { 0, 0, game->getWindowWidth(), game->getWindowHeight()};
	SDL_Renderer* renderer = game->getRenderer();
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 120, 0, 0, this->alpha);
	SDL_RenderFillRect(renderer, &screenRectangle);
	SDL_RenderDrawRect(renderer, &screenRectangle);
	SDL_Texture* front = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET, 
		game->getWindowWidth(), game->getWindowHeight());
	SDL_SetRenderTarget(renderer, front);

	while(alpha < SDL_ALPHA_OPAQUE)
	{
		this->alpha += 1;
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 120, 0, 0, this->alpha);
		SDL_RenderFillRect(renderer, &screenRectangle);
		SDL_RenderDrawRect(renderer, &screenRectangle);
		SDL_SetRenderTarget(renderer, front);

	}*/

	//SDL_Surface* s = SDL_CreateRGBSurface(0, game->getWindowWidth(), game->getWindowHeight(), 32, 0, 0, 0, 0);

	//SDL_Texture* t;
	////t = SDL_CreateTexture(game->getRenderer(), 32, 0, game->getWindowWidth(), game->getWindowHeight());
	//t = SDL_CreateTextureFromSurface(game->getRenderer(), s);
	//SDL_SetTextureAlphaMod(t, 255);
	////SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 0);
	//SDL_Texture* front = SDL_CreateTexture(game->getRenderer(), SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET,
	//	game->getWindowWidth(), game->getWindowHeight());
	//SDL_SetRenderTarget(game->getRenderer(), front);

	//SDL_SetRenderTarget(renderer, NULL);

	//SDL_RenderClear(renderer);
}

void Player::getScared(int amount)
{
	if (fearLevel_->getScared(amount))
		FadeOut();
}

/// <summary>
/// Contador para bajar cada maxCont_ amout a energy_
/// </summary>
/// <param name="amount"> cantidad que se le va añadir a energy_
void Player::drainEnergy(float amount)
{
	if (energyLevel_->drain(amount)) { // se queda dormido porque no tiene energía
		FadeOut();
	}
}

void Player::recoverEnergy(int amount)
{
}

void Player::recoverFear(int amount)
{
}

void Player::getMoney(int amount)
{
	money_ += amount;
}

void Player::removeMoney(int amount)
{
	money_ -= amount;
	if (money_ < 0) money_ = 0;
}

void Player::useObject(int index)
{
	inventory_->useObject(index);
}

bool Player::hasMissionObject()
{
	return inventory_->hasMissionObject();
}

void Player::addMissionObject(InventoryObject* p)
{
	inventory_->addMisionObject(p);
}

void Player::removeMissionObject()
{
	inventory_->removeMisionObject();
}


void Player::draw()
{
	//drawTexture(texture);
	animationManager->getFrameImagePlayer(getCollider(), textureRect, texture, timerAnimation/*, AnimationManager::PlayerState::Down*/,pair<int,int>(dirX_, dirY_));
	//drawDebug();
	energyLevel_->draw();
	fearLevel_->draw();
	if(boolrenderSleepText)NoSleepText();	
	//energyLevel_->drawDebug();
	if (inventoryVisibility)
		inventory_->draw();
}



//se le pasa una cantidad de dinero al player
//si la cantidad es negativa se entiende que es para una compra y se devuelve un bool como confirmacion
//en caso contrario solo se le añade el dinero al actual del jugador
bool Player::moneyChange(int money)
{
	if (money < 0 && money_ < money) return false;
	
	money_ += money;
	return true;
}
