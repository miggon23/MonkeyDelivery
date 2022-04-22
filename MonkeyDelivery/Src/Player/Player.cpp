#include "Player.h"
#include "../Items/Bike.h"
#include "../Items/Flashlight.h"
#include "../Items/Lantern.h"
#include "../Items/EnergyDrink.h"
#include "../Items/Skates.h"
#include "../Items/Pickaxe.h"
#include "../Logic/Game.h"
#include "SDL.h"


Player::Player(Game* game, AnimationManager* animation) :GameObject(game), animationManager(animation) {
	this->game = game;

	texture = nullptr;
	setTexture(monkeySS_Default);
	setOrientation("off");
	setMovState(WALKING);
	INIT_VEL_ = 1.0;

	//inicializacion de variables
	fear_ = 0;
	money_ = 0;
	vel_ = 0;
	orientation_ = "";
	runningSpeedFactor_ = 1.5;

	walkingEnergy_ = 0.05;
	runningEnergy_ = walkingEnergy_ * 1.5;
	decreasingEnergyLevel_ = walkingEnergy_; // Cambiar esto despu�s a un m�todo set <---

	resetVelocity(); //Se inicializa al valor de INIT_VEL_X e ..._Y

	setDimension(48, 54);
	setPosition(2000, 600);


	energyLevel_ = new energyLevel(game);
	fearLevel_ = new FearLevel(game);
	//fearBar_ = new FearBar(game);
	inventory_ = new Inventory(game, this, game->getRenderer());

	//Objetos de inventario
	inventory_->addObject(new Skates(game->getTexture(Item_Boots01), game));
	inventory_->addObject(new Flashlight(game->getTexture(Item_Lantern01), game));
	inventory_->addObject(new EnergyDrink(game->getTexture(Item_Soda), game));
	inventory_->addObject(new EnergyDrink(game->getTexture(Item_Soda), game));
	//inventory_->addObject(new Bike(new Texture(game->getRenderer(), "../Images/objects/patinete.png")));

	setInventoryVisibility(true);
	textureRect = { 0, 0, 16, 18 };
	timerAnimation = 0;
	//timer = sdlutils().virtualTimer();

	//// flashlight
	//flashlightTex_ = game->getTexture(shop_Boots01);
	//// lantern
	//lanternTex_ = game->getTexture(shop_Boots01);
	//// fadeout
	//fadeTex_ = game->getTexture(shop_Boots01);
	//fadeTex_->changeAlpha(0);
	fadeTex_ = game->getTexture(UI_Fade);
}

Player::~Player()
{
	delete energyLevel_;
	delete fearLevel_;
	delete inventory_;
	delete flashlightTex_; //CUIDADO!!!!
	delete lanternTex_; //CUIDADO!!!!
	
	flashlightTex_ = nullptr; //CUIDADO!!!!
	lanternTex_ = nullptr; //CUIDADO!!!!
	energyLevel_ = nullptr;
	fearLevel_ = nullptr;
	inventory_ = nullptr;
	std::cout << "PLAYER DELETED" << std::endl;
}

void Player::update()
{
	if (sleeping)
		sleep();//si esta durmiendo
	else move();//si no esta durmiendo habilitanmos el movimiento

	if ((energyLevel_->percentEnergy() == 0 || fearLevel_->percentFear() == 100) && !fade) {
		fade = true;
	}
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

	//Normalizamos el vector para que no se desplaze m�s en diagonal
	speed.normalize();
	speed = speed * vel_;

	if (dirX_ != 0 || dirY_ != 0) {
		if (isRunning) { //Esto se puede implementar desde el runCommand, evitando que el jugador tenga muchos estados como el de corriendo
			speed = speed * 1.5;			
		}

		// Comprobar si hay que cancelar el movimiento en alguna direcci�n por las colisiones
		if (topCollision && speed.getY() < 0  || bottomCollision && speed.getY() > 0) {
			speed = { speed.getX(), 0 };
		}
		if (leftCollision && speed.getX() < 0 || rightCollision && speed.getX() > 0) {
			speed = {0, speed.getY()};
		}

		drainEnergy(decreasingEnergyLevel_);
	}
	//setPosition(getPosition().getX() + dirX_, getPosition().getY() + dirY_);
	
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

void Player::sleep()
{
	getScared(-1);
	drainEnergy(-1);
	sdlutils().soundEffects().at("sleep").play(0, 1);
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

void Player::removeMoney(int amount)
{
	money_ -= amount;
	if (money_ < 0) money_ = 0;
}

void Player::draw() 
{
	if (!sleeping) {
		if (energyLevel_->percentEnergy() <= 20) 
			animationManager->setState(AnimationManager::PlayerState::GoToSleep);
		else if (fearLevel_->percentFear() >= 50)
			animationManager->setState(AnimationManager::PlayerState::Scared);
	}

	SDL_Rect pos = getCollider();

	pos.x -= game->getCamera()->getCameraPosition().getX();
	pos.y -= game->getCamera()->getCameraPosition().getY();
	
	animationManager->getFrameImagePlayer(pos, textureRect, texture, timerAnimation, AnimationManager::LastDir{ (int)dirX_, (int)dirY_ });

	energyLevel_->draw();
	fearLevel_->draw();

	if (boolrenderSleepText) NoSleepText();
	
	if (inventoryVisibility) inventory_->draw();

	if (usingFlashLight) {

		auto a = lightZoneFL();
		a.x -= game->getCamera()->getCameraPosition().getX();
		a.y -= game->getCamera()->getCameraPosition().getY();
		flashlightTex_->render(a);
	}

	if (usingLantern) {
		
		auto b = lightZoneL();
		b.x -= game->getCamera()->getCameraPosition().getX();
		b.y -= game->getCamera()->getCameraPosition().getY();
		lanternTex_->render(b);
	}

	if(fade)
	{
		fadeTex_->render({ 0, 0, 1800, 1000 }); // Renderizar la textura del rectangulo negro en ese rect

		FadeOut(); // Realiza un fadeout sobre la pantalla
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
		fadeTex_->render({ 0, 0, 1800, 1000 });


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
	sdlutils().soundEffects().at("scary").setVolume(game->getSoundEfectsVolume());
	sdlutils().soundEffects().at("scary").play(0, 1);
	setPosition((double) bedX_ + 15, bedY_);//colocar en la cama
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