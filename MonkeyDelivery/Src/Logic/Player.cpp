#include "Player.h"
#include "Inventory.h"
#include "Bike.h"<

Player::Player(Game* game) :GameObject(game) {
	this->game = game;
	
	texture = nullptr;
	setTexture(monkeyTexture);

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
	inventory_ = new Inventory(this);
	inventory_->addObject(new Bike());
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
	setTexture(monkeyEyesClosedTexture);
	draw();
	getScared(-1);
	drainEnergy(-1);
}

void Player::changeSleep()
{	
	if (energyLevel_->percentEnergy() <= 20.0||sleeping) {
		sleeping = !sleeping;
		//actulizo la textura
		if (sleeping) {
			setTexture(monkeyEyesClosedTexture);
		}
		else {
			setTexture(monkeyTexture);
		}
		draw();
	}
}

void Player::getScared(int amount)
{
	if (fearLevel_->getScared(amount))
		setTexture(monkeyEyesClosedTexture);
}

/// <summary>
/// Contador para bajar cada maxCont_ amout a energy_
/// </summary>
/// <param name="amount"> cantidad que se le va añadir a energy_
void Player::drainEnergy(float amount)
{
	if (energyLevel_->drain(amount)) { // se queda dormido porque no tiene energía
		setTexture(monkeyEyesClosedTexture);
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

void Player::draw()
{
	drawTexture(texture);
	//drawDebug();
	energyLevel_->draw();
	fearLevel_->draw();
	//energyLevel_->drawDebug();
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
