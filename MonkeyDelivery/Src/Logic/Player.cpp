#include "Player.h"
#include "Bike.h"
#include "Flashlight.h"
#include "Lantern.h"
#include "EnergyDrink.h"
#include "Skates.h"
#include "Game.h"
#include "SDL.h"


Player::Player(Game* game, AnimationManager* animation) :GameObject(game), animationManager(animation) {
	this->game = game;

	texture = nullptr;
	setTexture(monkeyspritesheet);
	setOrientation("off");
	setMovState(WALKING);
	INIT_VEL_ = 1.0;

	//inicializacion de variables
	fear_ = 0;
	money_ = 0;
	vel_ = 0;
	orientation_ = "";
	//walkingSpeed_ = 3;
	runningSpeedFactor_ = 1.5;

	walkingEnergy_ = 0.05;
	runningEnergy_ = walkingEnergy_ * 1.5;
	decreasingEnergyLevel_ = walkingEnergy_; // Cambiar esto después a un método set <---

	resetVelocity(); //Se inicializa al valor de INIT_VEL_X e ..._Y

	setDimension(90, 100);
	setPosition(game->getWindowWidth() / 2 - getWidth() / 2 , game->getWindowHeight() / 2 - getHeight() / 2);

	energyLevel_ = new energyLevel(game);
	fearLevel_ = new FearLevel(game);
	inventory_ = new Inventory(this, game->getRenderer());

	//Obketos de inventario
	inventory_->addObject(new Bike(new Texture(game->getRenderer(), "../Images/objects/patinete.png")));
	inventory_->addObject(new Flashlight(new Texture(game->getRenderer(), "../Images/objects/linterna2.png")));
	inventory_->addObject(new Lantern(new Texture(game->getRenderer(), "../Images/objects/linterna.png")));
	inventory_->addObject(new EnergyDrink(new Texture(game->getRenderer(), "../Images/objects/refresco.png")));
	inventory_->addObject(new Skates(new Texture(game->getRenderer(), "../Images/objects/patines.png")));

	setInventoryVisibility(true);
	textureRect = { 0, 0, 100, 100 };
	timerAnimation = 0;
	//timer = sdlutils().virtualTimer();

	// flashlight
	string path = "../Images/objects/luzprovi.png";
	flashlightTex_ = new Texture(game->getRenderer(), path);
	// lantern
	path = "../Images/objects/luzCircularProvi.png";
	lanternTex_ = new Texture(game->getRenderer(), path);
	// fadeout
	path = "../Images/ui/fade.png";
	fadeTex_ = new Texture(game->getRenderer(), path);
	fadeTex_->changeAlpha(0);
}

Player::~Player()
{
	delete energyLevel_;
	delete fearLevel_;
	delete inventory_;
	delete flashlightTex_;
	delete lanternTex_;
	delete fadeTex_;
	energyLevel_ = nullptr;
	fearLevel_ = nullptr;
	inventory_ = nullptr;
	std::cout << "PLAYER DELETED" << std::endl;
}

void Player::update()
{
	if (sleeping)sleep();//si esta durmiendo
	else move();//si no esta durmiendo habilitanmos el movimiento

	/*if ((energyLevel_->percentEnergy() == 0 || fearLevel_->percentFear() == 100) && !fade) {
		fade = true;
	}*/
	if((fearLevel_->getScared(0) || energyLevel_->drain(0)) && !fade) {
		fade = !fade;
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

void Player::sleep()
{
	//std::cout << "A MIMIR YA PUTO MONO" << endl;
	//cambio la textura
	//setTexture(monkeyEyesClosedTexture);
	//draw();
	getScared(-1);
	drainEnergy(-1);
	sdlutils().soundEffects().at("sleep").play(0, 1);
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
	if (usingFlashLight) {
		/*Box(lightZone(), BLUE).render(game->getRenderer());*/
		//usingLantern = false;
		auto a = lightZoneFL();
		flashlightTex_->render(a);
	}
	if (usingLantern) {
		//usingFlashLight = false;
		auto b = lightZoneL();
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
		fade = !fade;
		alpha = 0;
		fadeTex_->changeAlpha(alpha);
		fadeTex_->render({ 0, 0, 1800, 1000 });

		// Reestablece el miedo y la energía al valor por defecto
		fearLevel_->resetFear();
		energyLevel_->resetEnergy();

		// Establece la posición en la cama más cercana
		sendToBed();
	}
}

void Player::sendToBed()
{
	sdlutils().soundEffects().at("scary").setVolume(game->getSoundEfectsVolume());
	sdlutils().soundEffects().at("scary").play(0, 1);
}

//se le pasa una cantidad de dinero al player
//si la cantidad es negativa se entiende que es para una compra y se devuelve un bool como confirmacion
//en caso contrario solo se le añade el dinero al actual del jugador
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