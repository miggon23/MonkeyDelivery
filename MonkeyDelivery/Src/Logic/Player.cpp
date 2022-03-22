#include "Player.h"
#include "Inventory.h"
#include "Bike.h"
#include "Flashlight.h"
#include "EnergyDrink.h"
#include "Skates.h"
#include "Game.h"
#include "SDL.h"


Player::Player(Game* game, AnimationManager* animation) :GameObject(game), animationManager(animation) {
	this->game = game;

	texture = nullptr;
	setTexture(monkeyspritesheet);

	setMovState(WALKING);
	INIT_VEL_ = 3.0;

	//inicializacion de variables
	fear_ = 0;
	money_ = 0;
	vel_ = 0;
	orientation_ = "";
	//walkingSpeed_ = 3;
	runningSpeedFactor_ = 1.5;

	walkingEnergy_ = 0.5;
	runningEnergy_ = 1.0;
	decreasingEnergyLevel_ = walkingEnergy_; // Cambiar esto después a un método set <---

	resetVelocity(); //Se inicializa al valor de INIT_VEL_X e ..._Y

	setDimension(90, 100);
	setPosition(game->getWindowWidth() / 2 - getWidth() / 2 , game->getWindowHeight() / 2 - getHeight() / 2);

	energyLevel_ = new energyLevel(game);
	fearLevel_ = new FearLevel(game);
	inventory_ = new Inventory(this, game->getRenderer());

	//Obketos de inventario
	inventory_->addObject(new Bike(new Texture(game->getRenderer(), "../Images/objects/linterna.png")));
	inventory_->addObject(new Flashlight(new Texture(game->getRenderer(), "../Images/objects/linterna2.png")));
	inventory_->addObject(new EnergyDrink(new Texture(game->getRenderer(), "../Images/objects/refresco.png")));
	//inventory_->addObject(new Skates(new Texture(game->getRenderer(), "../Images/objects/refresco.png")));

	setInventoryVisibility(true);
	textureRect = { 0, 0, 100, 100 };
	timerAnimation = 0;
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
	Vector2D<double> speed = { (double)dirX_, (double)dirY_ };
	speed.set(dirX_, dirY_);

	//Normalizamos el vector para que no se desplaze más en diagonal
	speed.normalize();
	speed = speed * vel_;

	if (dirX_ != 0 || dirY_ != 0) {
		//if (isRunning) { //Esto se puede implementar desde el runCommand, evitando que el jugador tenga muchos estados como el de corriendo
		//	speed = speed * 1.5;			
		//}
		
		// CAMARA
		//Vector2D<float> a = { (float)getX(), (float)getY() };

		//game->getCamera()->setPos({ (float)speed.getX(),(float)speed.getY() });
		game->aPlayerPos((float)speed.getX(), (float)speed.getY());
		
		drainEnergy(decreasingEnergyLevel_);
	}

	//HAY QUE NORMALIZAR EL VECTOR
	//setPosition(getX() + speed.getX(), getY() + speed.getY());

}

void Player::setIsRunning(bool run)
{
	isRunning = run;
	if (isRunning) {
		decreasingEnergyLevel_ = runningEnergy_;
		setVel(getVel() * runningSpeedFactor_);
	}
	else
	{
		decreasingEnergyLevel_ = walkingEnergy_;
		setVel(getVel() / runningSpeedFactor_);
	}

}

/// <summary>
/// Resetea la velocidad del jugador a la de por defecto (sin modificaciones)
/// </summary>
void Player::resetVelocity()
{
	setVel(INIT_VEL_);
}

void Player::sleep()
{
	//std::cout << "A MIMIR YA PUTO MONO" << endl;
	//cambio la textura
	//setTexture(monkeyEyesClosedTexture);
	//draw();
	getScared(-1);
	drainEnergy(-1);
}

//cambiar la variable de dormir y establecer la textura
void Player::changeSleep()
{
	if (energyLevel_->percentEnergy() <= 20.0 || sleeping) {
		sleeping = !sleeping;
		//actulizo la textura
		if (sleeping) {
			animationManager->setState(AnimationManager::PlayerState::Sleeping);
			if (usingFlashLight) {
				usingFlashLight = false;
				flashLOn = true;
				setOrientation("off");
			}

		}
		else {
			animationManager->setState(AnimationManager::PlayerState::Running);
			if (flashLOn) {
				usingFlashLight = true;
				flashLOn = false;
			}
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

bool Player::inventoryFull()
{
	return inventory_->inventoryFull();
}

void Player::addObjectToInventory(InventoryObject* p)
{
	inventory_->addObject(p);
}

void Player::draw() 
{
	if (!sleeping) {
		if (energyLevel_->percentEnergy() <= 20) 
			animationManager->setState(AnimationManager::PlayerState::GoToSleep);
		else if (fearLevel_->percentFear() >= 50)
			animationManager->setState(AnimationManager::PlayerState::Scared);
	}

	//SDL_Rect pos = { game->getWindowWidth() / 2 - getWidth() / 2, game->getWindowHeight() / 2 - getHeight() / 2 , getWidth(), getHeight()};
	/*SDL_Rect pos = getCollider();
	pos.x -= game->getCamera()->getCameraCenterPosition().getX();
	pos.y -= game->getCamera()->getCameraCenterPosition().getY();
	pos.x -= game->getCamera()->getWidth()/2;
	pos.y -= game->getCamera()->getHeight()/2;*/
	//animationManager->getFrameImagePlayer(pos, textureRect, texture, timerAnimation, AnimationManager::LastDir{ dirX_, dirY_ });
	animationManager->getFrameImagePlayer(getCollider(), textureRect, texture, timerAnimation, AnimationManager::LastDir{ dirX_, dirY_ });

	//drawDebug();
	energyLevel_->draw();
	fearLevel_->draw();
	if (boolrenderSleepText)
		NoSleepText();
	//energyLevel_->drawDebug();
	if (inventoryVisibility)
		inventory_->draw();
	if (usingFlashLight)
		Box(lightZone(), BLUE).render(game->getRenderer());
}

//se le pasa una cantidad de dinero al player
//si la cantidad es negativa se entiende que es para una compra y se devuelve un bool como confirmacion
//en caso contrario solo se le añade el dinero al actual del jugador
bool Player::moneyChange(int money)
{
	if (money < 0 && money_ < abs(money))
		return false;

	money_ += money;
	return true;
}
//linterna
const SDL_Rect Player::lightZone()
{
	if (isAsleep()) {
		return{ 0,0,0, 0 };
	}
	SDL_Rect hitZone{ int(getX() + 50),
					int(getY()),
					getWidth(),
					getHeight() + 50
	};
	//ejeX
	if (dirX_ == 1 /*&& dirY_==0*/) {
		hitZone = { int(getX() + 50),
					int(getY()),
					getWidth() + 50,
					getHeight() };
		setOrientation("right");
	}
	else if (dirX_ == -1 /*&& dirY_==0*/)
	{
		hitZone = { int(getX() - 100),
					int(getY()),
					getWidth() + 50 ,
					getHeight() };
		setOrientation("left");
	}
	else if (/*dirX_ == 1 &&*/ dirY_ == -1)
	{
		hitZone = { int(getX()),
					int(getY() - 100),
					getWidth(),
					getHeight() + 50 };
		setOrientation("up");
	}
	else if (dirY_ == 1)
	{
		hitZone = { int(getX()),
					int(getY() + 50),
					getWidth(),
					getHeight() + 50 };
		setOrientation("down");

	}
	else if (dirX_ == 0 && dirY_ == 0)
	{
		if (getOrientation() == "left")
			hitZone = { int(getX() - 100),
					int(getY()),
					getWidth() + 50,
					getHeight() };
		else if (getOrientation() == "right")
			hitZone = { int(getX() + 50),
					int(getY()),
					getWidth() + 50 ,
					getHeight() };
		else if (getOrientation() == "up")
			hitZone = { int(getX()),
					int(getY() - 100),
					getWidth(),
					getHeight() + 50 };
		else if (getOrientation() == "down")
			hitZone = { int(getX()),
					int(getY() + 50),
					getWidth(),
					getHeight() + 50 };
		else
			hitZone = getCollider();
	}
	return hitZone;
}


