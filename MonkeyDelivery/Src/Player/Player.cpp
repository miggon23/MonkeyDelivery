#include "Player.h"
#include <math.h>
#include <climits>
#include "../Items/Bike.h"
#include "../Items/Flashlight.h"
#include "../Items/Lantern.h"
#include "../Items/EnergyDrink.h"
#include "../Items/Skates.h"
#include "../Items/Pickaxe.h"
#include "../Items/Repel.h"
#include "../Items/Monkeycola.h"
#include "../Items/Banana.h"
#include "../Logic/Game.h"
#include "../Logic/PowerUpsManager.h"
#include "SDL.h"


Player::Player(Game* game) :GameObject(game), animationManager(AnimationManager::Instance()) {
	this->game = game;

	texture = nullptr;
	setTexture(monkeySS_Default);
	setOrientation("off");
	setMovState(WALKING);
	setFlip(SDL_FLIP_NONE);
	INIT_VEL_ = 0.225;

	//inicializacion de variables
	fear_ = 0;
	money_ = 0;
	vel_ = 0;
	orientation_ = "";
	runningSpeedFactor_ = 1.5;

	walkingEnergy_ = 0.025;
	runningEnergy_ = walkingEnergy_ * 1.5;
	decreasingEnergyLevel_ = walkingEnergy_; 
	reducedSpeed_ = false;
	reduceFactor_ = 2;
	maxEnergyPercent_ = 20;
	reduceEnergyFactor_ = 0.025;
	isStopped_ = false;

	resetVelocity(); //Se inicializa al valor de INIT_VEL_X e ..._Y

	Point2D<double> relative = { (double)(game->getWindowWidth() / 1800), (double)(game->getWindowHeight() / 1000) };

	setDimension(48, 54);
	setPosition(4050 * relative.getX(), 1800 * relative.getY());

	lastUpdate = timer.currTime();
	flashlightTex_ = game->getTexture(lightGeneric);
	lanternTex_ = game->getTexture(lanternCircular);
	energyLevel_ = new energyLevel(game);
	fearLevel_ = new FearLevel(game);
	playerHUD_ = new playerHUD(game);

	inventory_ = new Inventory(game, this, game->getRenderer());
	powerUpsManager = new PowerUpsManager(this->game, this);
	//Objetos de inventario
	inventory_->addObject(new Skates(game->getTexture(Item_Boots01), game, this));
	inventory_->addObject(new Flashlight(game->getTexture(Item_Lantern01), game, this));
	inventory_->addObject(new EnergyDrink(game->getTexture(Item_Soda02), game, this));
	
	inventory_->addObject(new Repel(game->getTexture(Item_Spray), game,this));
	setInventoryVisibility(true);
	textureRect = { 0, 0, 16, 18 };
	timerAnimation = 0;

	fadeTex_ = game->getTexture(UI_Fade);

	xMoney = (int)(game->getWindowWidth() / 10.91);
	yMoney = yChests = (int)(game->getWindowHeight() / 7.30);
	xChest = (int)(game->getWindowWidth() / 5.625);

	// Iconos sobre el player
	scaredIcon = game->getTexture(monkeyScared_Icon);
	tiredIcon = game->getTexture(monkeyTired_Icon);
 	scaredRect = { (int)game->getWindowWidth() / 2, (int)game->getWindowHeight() / 2 - 60, 60, 60 };
	tiredRect = { (int)game->getWindowWidth() / 2, (int)game->getWindowHeight() / 2 - 60, 70, 70 };
	
	totalChest = 8;
}

Player::~Player()
{
	delete energyLevel_;		energyLevel_ = nullptr;
	delete fearLevel_;			fearLevel_ = nullptr;
	delete playerHUD_;			playerHUD_ = nullptr;
	delete inventory_;			inventory_ = nullptr;
	delete powerUpsManager;		powerUpsManager = nullptr;
	std::cout << "PLAYER DELETED" << std::endl;
}

void Player::update()
{
	cout << vel_ << endl;
	if (!fade && !isTalking_ && !isInTutorial_) {

		powerUpsManager->update();
		if (sleeping)
		{
			sleep();//si esta durmiendo
			if (energyLevel_->percentEnergy() == 100.0)
				changeSleep();
		}
			
		else move();//si no esta durmiendo habilitanmos el movimiento

		if (fearLevel_->percentFear() == 100) {
			fade = true;
			removeMoney(20);
		}
		if (energyLevel_->percentEnergy() == 0 && !reducedSpeed_)
		{
			previusVel_ = getVel();
			reducedSpeed_ = true;
			setVel(getVel() / reduceFactor_);
		}
		else if (energyLevel_->percentEnergy() > 0 && reducedSpeed_) { 
			reducedSpeed_ = false;
			setVel(getVel() * reduceFactor_);
		}
	}
	lastUpdate = timer.currTime();
}

void Player::move()
{
	Vector2D<double> speed = { (double)dirX_, (double)dirY_ };
	
	//Normalizamos el vector para que no se desplaze m�s en diagonal
	speed.normalize();
	

	//SI LA VELOCIDAD ES 0 RECUPERA ENERGIA HASTA UN MAX
	if (speed.getX() == 0 && speed.getY() == 0) {
		isStopped_ = true;
		if (energyLevel_->percentEnergy() < maxEnergyPercent_) {
			energyLevel_->drain(-reduceEnergyFactor_);
		}
	}
	else isStopped_ = false;

	//speed = speed * vel_ * (timer.currTime() - lastUpdate);
	speed = speed * vel_ * (game->getTimer()->DeltaTime()*1000);

	if (dirX_ != 0 || dirY_ != 0) {

		// Comprobar si hay que cancelar el movimiento en alguna direcci�n por las colisiones
		if (topCollision && speed.getY() < 0 || bottomCollision && speed.getY() > 0) {
			speed = { speed.getX(), 0 };
		}
		if (leftCollision && speed.getX() < 0 || rightCollision && speed.getX() > 0) {
			speed = { 0, speed.getY() };
		}

		drainEnergy(decreasingEnergyLevel_);
	}
	setPosition(getPosition().getX() + speed.getX(), getPosition().getY() + speed.getY());
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

void Player::sleep(){
	recoverFear(1);
	drainEnergy(-0.4);
}

//cambiar la variable de dormir y establecer la textura
void Player::changeSleep()
{
	if (energyLevel_->percentEnergy() <= maxEnergyPercent_ || sleeping || fade) {
		sleeping = !sleeping;
		//actulizo la textura
		if (sleeping) {
			if (reducedSpeed_) {
				reducedSpeed_ = false;
				setVel(getVel() * reduceFactor_);
			}

			animationManager->setState(AnimationManager::PlayerState::Sleeping);
			if (usingFlashLight) {
				usingFlashLight = false;
				flashLOn = true;
				setOrientation("off");
			}
			if (usingLantern) {
				usingLantern = false;
				lanternOn = true;
			}
			sdlutils().soundEffects().at("sleep").setVolume((int)(game->getGeneralVolume() * game->getSoundEfectsVolume()));
			sdlutils().soundEffects().at("sleep").play(-1, 1);
			inventory_->changeSelectedObject(0);
		}
		else {
			//recoloca al player en su posición anterior
			setPosition(posBeforeSleep.getX(), posBeforeSleep.getY());
			
			animationManager->setState(AnimationManager::PlayerState::Running);
			if (flashLOn) {
				usingFlashLight = true;
				flashLOn = false;
			}
			if (lanternOn) {
				usingLantern = true;
				lanternOn = false;
			}
			sdlutils().soundEffects().at("sleep").pauseChannel(1);
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
	int x = 80;
	int y = 200;
	//Textos q renderiza
	vector<string> texts = {
			"Ahora No Puedes Dormir "," ",
			"Tienes Mucha Energia"
	};

	game->renderText(texts, x, y, 20, 20);
	//si ya ha pasado el tiempo desactivo
	if (SDL_GetTicks() - timerSleepText >= 3000)boolrenderSleepText = false;
}

void Player::removeMoney(int amount)
{
	money_ -= amount;
	if (money_ < 0) money_ = 0;
}

void Player::pausePowerUps()
{
	powerUpsManager->onPauseEnter();
}
void Player::resumePowerUps()
{
	powerUpsManager->onPauseExit();
}

void Player::desactivatePowerUp(PowerUps p)
{
	powerUpsManager->desactivate(p);
}

void Player::initPowerUp(PowerUps x) {
	powerUpsManager->ActivatePowerUp(x);
}

void Player::initPowerUp(PowerUps x, double value)
{
	powerUpsManager->ActivatePowerUp(x, value);
}

void Player::draw()
{
	if (!isInTutorial_) { // no dibujamos nada si estamos en el tutorial

		if (!sleeping) {
			if (isWearingGreenBoots) setTexture(monkeySS_GreenBoots);
			else if (isWearingOrangeBoots) setTexture(monkeySS_OrangeBoots);
			else setTexture(monkeySS_Default);

			if (fearLevel_->percentFear() >= 50 && isStopped_) {
				animationManager->setIsScared(true);
				animationManager->setState(AnimationManager::PlayerState::Idle);
				scaredIcon->render(scaredRect);
			}
			else if (fearLevel_->percentFear() >= 50) {
				animationManager->setState(AnimationManager::PlayerState::Scared);
				scaredIcon->render(scaredRect);
			}
			else if (energyLevel_->percentEnergy() <= 20 && isStopped_) { 
				animationManager->setIsTired(true); 
				animationManager->setState(AnimationManager::PlayerState::Idle);
				tiredIcon->render(tiredRect);
			}
			else if (energyLevel_->percentEnergy() <= 20) {
				animationManager->setState(AnimationManager::PlayerState::GoToSleep);
				tiredIcon->render(tiredRect);
			}
			else if (isStopped_)
				animationManager->setState(AnimationManager::PlayerState::Idle);
			else animationManager->setState(AnimationManager::PlayerState::Running);
		}

		SDL_Rect pos = getCollider();

		pos.x -= (int)game->getCamera()->getCameraPosition().getX();
		pos.y -= (int)game->getCamera()->getCameraPosition().getY();

		animationManager->getFrameImagePlayer(pos, textureRect, texture, timerAnimation, AnimationManager::LastDir{ (int)dirX_, (int)dirY_ });

		playerHUD_->drawFillHUD();		
		energyLevel_->draw();
		fearLevel_->draw();
		playerHUD_->drawOverHUD();
		
		game->renderMoney(to_string(money_), xMoney, yMoney, SDL_Color{255,255,255,255});
		game->renderMoney(to_string(totalChest), xChest, yChests);
		powerUpsManager->draw();

		if (boolrenderSleepText) NoSleepText();

		if (inventoryVisibility) inventory_->draw();

		if (usingFlashLight) {

			auto a = lightZoneFL();
			a.x -= (int)game->getCamera()->getCameraPosition().getX();
			a.y -= (int)game->getCamera()->getCameraPosition().getY();

			if (orientation_ == "right") // dcha
				flashlightTex_->render(a);
			else if (orientation_ == "left") // izqda
				flashlightTex_->render(a, SDL_FLIP_HORIZONTAL);
			else if (orientation_ == "up") // arriba
				flashlightTex_->render(a, -90.0);
			else // abajo y por defecto
				flashlightTex_->render(a, 90.0);
		}

		if (usingLantern) {

			auto b = lightZoneL();
			b.x -= (int)game->getCamera()->getCameraPosition().getX();
			b.y -= (int)game->getCamera()->getCameraPosition().getY();
			lanternTex_->render(b);
		}

		if (fade)
		{
			fadeTex_->render({ 0, 0, (int)game->getWindowWidth(), (int)game->getWindowHeight() }); // Renderizar la textura del rectangulo negro en ese rect
			FadeOut(); // Realiza un fadeout sobre la pantalla
		}
	}
}

void Player::FadeOut()
{
	if (alpha < SDL_ALPHA_OPAQUE && timer.currTime() > 50)
	{
		alpha += 5;
		fadeTex_->changeAlpha(alpha);
		timer.reset();
	}
	else if (alpha >= SDL_ALPHA_OPAQUE)
	{
		alpha = 0;
		fadeTex_->changeAlpha(alpha);

		// Establece la posici�n en la cama m�s cercana
		sendToBed();
		// Reestablece el miedo y la energ�a al valor por defecto
		fearLevel_->resetFear();
		energyLevel_->resetEnergy();
	}
}

Point2D<double> Player::getClosestBed()
{
	int min = INT_MAX;
	Point2D<double> p;
	for (auto b : game->getBeds())
	{
		int x = std::abs(b->getX() - getX());
		int y = std::abs(b->getY() - getY());
		int val = x + y;
		if (val < min) { min = val; p.setX(b->getX()); p.setY(b->getY()); }
	}
	return p;
}

double Player::getDistanceXToClosestBed()
{
	return std::abs(getPosition().getX() - getClosestBed().getX());
	
}
double Player::getDistanceYToClosestBed()
{
	return std::abs(getPosition().getY() - getClosestBed().getY());

}

void Player::sendToBed()
{
	fade = false;
	reducedSpeed_ = false;
	powerUpsManager->desactivateAllPowerUps();
	resetVelocity();
	inventory_->desactivateUseSelectedObject();
	sdlutils().soundEffects().at("scary").setVolume((int)(game->getSoundEfectsVolume() * game->getGeneralVolume()));
	sdlutils().soundEffects().at("scary").play(0, 1);

	Point2D<double> p;
	p=getClosestBed();
	
	setPosition(p.getX() , p.getY() + 60.0);//colocar en la cama

	game->resetInitialTransition();
}



/// <summary>
/// Manejar velocidad al chocar con una pared
/// </summary>
/// <param name="dir"> direccion en la que se cancela la velocidad</param> 
void Player::onCollision(int dir)
{
	switch (dir) {
	case LEFT:
		leftCollision = true;
		break;
	case UP:
		topCollision = true;
		break;
	case RIGHT:
		rightCollision = true;
		break;
	case DOWN:
		bottomCollision = true;
		break;
	default:break;
	}
}

/// <summary>
/// Manejar velocidad al dejar de chocar con una pared
/// </summary>
void Player::onCollisionExit() {
	leftCollision = false;
	topCollision = false;
	rightCollision = false;
	bottomCollision = false;
}

bool Player::getFadeOut(){
	return fade;
}

//se le pasa una cantidad de dinero al player
//si la cantidad es negativa se entiende que es para una compra y se devuelve un bool como confirmacion
//en caso contrario solo se le a�ade el dinero al actual del jugador
bool Player::moneyChange(int money)
{
	if (money < 0 && money_ < abs(money))
		return false;

	money_ += money;

	if (money > 0)
	{
		sdlutils().soundEffects().at("getMoney").setVolume(game->getSoundEfectsVolume());
		sdlutils().soundEffects().at("getMoney").play(0, 1);
	}

	return true;
}

//linterna
const SDL_Rect Player::lightZoneFL()
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
	if (dirX_ == 1) {
		hitZone = { int(getX() + 50),
					int(getY()),
					getWidth() + 50,
					getHeight() };
		setOrientation("right");
	}
	else if (dirX_ == -1)
	{
		hitZone = { int(getX() - 100),
					int(getY()),
					getWidth() + 50 ,
					getHeight() };
		setOrientation("left");
	}
	else if (dirY_ == -1)
	{
		hitZone = { int(getX() - 25),
					int(getY() - 75),
					getHeight() + 50 , getWidth() };
		setOrientation("up");
	}
	else if (dirY_ == 1)
	{
		hitZone = { int(getX() - 25),
					int(getY() + 75),
					getHeight() + 50,
					getWidth() };
		setOrientation("down");

	}
	else if (dirX_ == 0 && dirY_ == 0)
	{
		if (getOrientation() == "left") {
			hitZone = { int(getX() - 100),
					int(getY()),
					getWidth() + 50,
					getHeight() };
		}
		else if (getOrientation() == "right") {
			hitZone = { int(getX() + 50),
					int(getY()),
					getWidth() + 50 ,
					getHeight() };
		}

		else if (getOrientation() == "up") {
			hitZone = { int(getX() - 25),
					int(getY() - 75),
					getHeight() + 50 , getWidth() };
		}

		else if (getOrientation() == "down") {
			hitZone = { int(getX() - 25),
			int(getY() + 75),
			getHeight() + 50,
			getWidth() };
		}
		else {
			hitZone = getCollider();
		}
	}
	return hitZone;
}

const SDL_Rect Player::lightZoneL()
{
	if (isAsleep()) {
		return{ 0,0,0, 0 };
	}
	SDL_Rect hitZone{ int(getX() - 75),
 					int(getY() - 75),
					getWidth()*4,
					getHeight()*4
	};
	return hitZone;
}

void Player::addPickaxe(int level)
{
	switch (level)
	{
	case 1:
		inventory_->addObject(new Pickaxe(game->getTexture(Item_pickaxe01), game, level, this));
		break;
	case 2:
		inventory_->addObject(new Pickaxe(game->getTexture(Item_pickaxe02), game, level, this));
		break;
	default:
		break;
	}
}