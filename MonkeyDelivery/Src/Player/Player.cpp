#include "Player.h"
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


Player::Player(Game* game, AnimationManager* animation) :GameObject(game), animationManager(animation) {
	this->game = game;

	texture = nullptr;
	setTexture(monkeySS_Default);
	setOrientation("off");
	setMovState(WALKING);
	setFlip(SDL_FLIP_NONE);
	INIT_VEL_ = 0.225;

	//inicializacion de variables
	fear_ = 0;
	money_ = 100;
	vel_ = 0;
	orientation_ = "";
	runningSpeedFactor_ = 1.5;

	walkingEnergy_ = 0.05;
	runningEnergy_ = walkingEnergy_ * 1.5;
	decreasingEnergyLevel_ = walkingEnergy_; // Cambiar esto despu�s a un m�todo set <---
	reducedSpeed_ = false;
	reduceFactor_ = 2.2;
	maxEnergyPercent_ = 45;
	reduceEnergyFactor_ = 0.1;
	isStopped_ = false;

	resetVelocity(); //Se inicializa al valor de INIT_VEL_X e ..._Y

	setDimension(48, 54);
	setPosition(4050, 1800);

	lastUpdate = timer.currTime();
	flashlightTex_ = game->getTexture(Item_Boots01);
	energyLevel_ = new energyLevel(game);
	fearLevel_ = new FearLevel(game);
	playerHUD_ = new playerHUD(game);

	inventory_ = new Inventory(game, this, game->getRenderer());
	powerUpsManager = new PowerUpsManager(this->game, this);
	//Objetos de inventario
	inventory_->addObject(new Skates(game->getTexture(Item_Boots01), game, this));
	inventory_->addObject(new Flashlight(game->getTexture(Item_Lantern01), game, this));
	inventory_->addObject(new EnergyDrink(game->getTexture(Item_Soda02), game, this));
	//inventory_->addObject(new Monkeycola(game->getTexture(Item_Soda01), game, this));
	//inventory_->addObject(new Banana(game->getTexture(Item_Banana), game,this));
	inventory_->addObject(new Repel(game->getTexture(Item_Spray), game,this));
	setInventoryVisibility(true);
	textureRect = { 0, 0, 16, 18 };
	timerAnimation = 0;
	//timer = sdlutils().virtualTimer();

	fadeTex_ = game->getTexture(UI_Fade);
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
	if (!fade && !isTalking_ && !isInTutorial_) {

		powerUpsManager->update();
		if (sleeping)
			sleep();//si esta durmiendo
		else move();//si no esta durmiendo habilitanmos el movimiento

		if (fearLevel_->percentFear() == 100) {
			fade = true;
			removeMoney(20);
		}
		if (energyLevel_->percentEnergy() == 0 && !reducedSpeed_)
		{
			previusVel_ = getVel();
			reducedSpeed_ = true;
			setVel(INIT_VEL_ / reduceFactor_);
		}
		else if (energyLevel_->percentEnergy() != 0) { reducedSpeed_ = false;}
	}
	lastUpdate = timer.currTime();
}

void Player::move()
{
	Vector2D<double> speed = { (double)dirX_, (double)dirY_ };

	//Normalizamos el vector para que no se desplaze m�s en diagonal
	speed.normalize();
	speed = speed * vel_ * (timer.currTime() - lastUpdate);

	if (dirX_ != 0 || dirY_ != 0) {
		if (isRunning) { //Esto se puede implementar desde el runCommand, evitando que el jugador tenga muchos estados como el de corriendo
			speed = speed * 1.05;
		}

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

	//std::cout << speed.magnitude() << endl;

	//SI LA VELOCIDAD ES 0 RECUPERA ENERGIA HASTA UN MAX
	if (speed.getX() == 0 && speed.getY() == 0) {
		isStopped_ = true;
		if (energyLevel_->percentEnergy() < maxEnergyPercent_) {
			energyLevel_->drain(-reduceEnergyFactor_);
			if (energyLevel_->percentEnergy() <= reduceEnergyFactor_)
				setVel(previusVel_);
		}
	}
	else isStopped_ = false;
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
	drainEnergy(-0.1);
}

//cambiar la variable de dormir y establecer la textura
void Player::changeSleep()
{
	if (energyLevel_->percentEnergy() <= 20.0 || sleeping || fade) {
		sleeping = !sleeping;
		//actulizo la textura
		if (sleeping) {
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
		}
		else {
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
	int x = (int)game->getWindowWidth() / 2 - 250;
	int y = (int)game->getWindowHeight() / 2 - 50;
	//Textos q renderiza
	vector<string> texts = {
			"No Puedes Dormir "," ",
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

void Player::initPowerUp(PowerUps x) {
	powerUpsManager->ActivatePowerUp(x);
}

void Player::draw()
{
	if (!isInTutorial_) { // no dibujamos nada si estamos en el tutorial

		if (!sleeping) {
			if (energyLevel_->percentEnergy() <= 20 && isStopped_) { 
				animationManager->setIsTired(true); 
				animationManager->setState(AnimationManager::PlayerState::Idle);
			}
			else if (energyLevel_->percentEnergy() <= 20)
				animationManager->setState(AnimationManager::PlayerState::GoToSleep);
			else if (fearLevel_->percentFear() >= 50)
				animationManager->setState(AnimationManager::PlayerState::Scared);
			else if (isStopped_)
				animationManager->setState(AnimationManager::PlayerState::Idle);
			else animationManager->setState(AnimationManager::PlayerState::Running);
		}

		SDL_Rect pos = getCollider();

		pos.x -= (int)game->getCamera()->getCameraPosition().getX();
		pos.y -= (int)game->getCamera()->getCameraPosition().getY();

		animationManager->getFrameImagePlayer(pos, textureRect, texture, timerAnimation, AnimationManager::LastDir{ (int)dirX_, (int)dirY_ });


		energyLevel_->draw();
		fearLevel_->draw();
		playerHUD_->draw();
		game->renderMoney(to_string(money_), 265, 134);
		powerUpsManager->draw();

		if (boolrenderSleepText) NoSleepText();

		if (inventoryVisibility) inventory_->draw();

		if (usingFlashLight) {

			auto a = lightZoneFL();
			a.x -= (int)game->getCamera()->getCameraPosition().getX();
			a.y -= (int)game->getCamera()->getCameraPosition().getY();
			flashlightTex_->render(a);
		}

		if (usingLantern) {

			auto b = lightZoneL();
			b.x -= (int)game->getCamera()->getCameraPosition().getX();
			b.y -= (int)game->getCamera()->getCameraPosition().getY();
			lanternTex_->render(b);
		}

		if (fade)
		{
			fadeTex_->render({ 0, 0, 1800, 1000 }); // Renderizar la textura del rectangulo negro en ese rect
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
		//fadeTex_->render({ 0, 0, 1800, 1000 });


		// Establece la posici�n en la cama m�s cercana
		sendToBed();
		// Reestablece el miedo y la energ�a al valor por defecto
		fearLevel_->resetFear();
		energyLevel_->resetEnergy();
	}
}

void Player::sendToBed()
{
	fade = false;
	powerUpsManager->desactivateAllPowerUps();
	inventory_->desactivateUseSelectedObject();
	sdlutils().soundEffects().at("scary").setVolume((int)(game->getSoundEfectsVolume() * game->getGeneralVolume()));
	sdlutils().soundEffects().at("scary").play(0, 1);
	setPosition((double)bedX_ + 15, bedY_);//colocar en la cama
}

/// <summary>
/// Manejar velocidad al chocar con una pared
/// </summary>
/// <param name="ud"> direccion en la que se cancela la velocidad</param> 
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
		if (getOrientation() == "left") {
			hitZone = { int(getX() - 100),
					int(getY()),
					getWidth() + 50,
					getHeight() };

			//SDL_RenderCopy(renderer, flashlightSides, NULL, &hitzone);
			//setTexture(flashlightSides);
		}
		else if (getOrientation() == "right") {
			hitZone = { int(getX() + 50),
					int(getY()),
					getWidth() + 50 ,
					getHeight() };
			//setTexture(flashlightSides);
		}

		else if (getOrientation() == "up") {
			hitZone = { int(getX()),
					int(getY() - 100),
					getWidth(),
					getHeight() + 50 };
			//setTexture(flashlightUp);
		}

		else if (getOrientation() == "down") {
			hitZone = { int(getX()),
					int(getY() + 50),
					getWidth(),
					getHeight() + 50 };
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
	SDL_Rect hitZone{ int(getX()),
					int(getY()),
					getWidth(),
					getHeight()
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