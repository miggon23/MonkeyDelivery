#include "Player.h"
#include "Inventory.h"
#include "Bike.h"

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

	setPosition(15, 100);
	setDimension(90, 100);

	energyLevel_ = new energyLevel(game);
	inventory_ = new Inventory(game, this);
	inventory_->addObject(new Bike(game));
}

Player::~Player()
{
	delete energyLevel_;
	delete inventory_;
	energyLevel_ = nullptr;
	inventory_ = nullptr;
}

void Player::update()
{
	move(pair<double, double>(velX, velY));
}

/// <summary>
/// Se le suma a la pos la x y la y del parametro
/// </summary>
/// <param name="speed"> La primera componente es la x y la segunda la y</param>
void Player::move(pair<double, double> speed)
{
	if (velX != 0 || velY != 0) {
		if (isRunning) { 
			setPosition(getX() + speed.first*2, getY() + speed.second*2); 
			drainEnergy(runningEnergy_);
		}
		else{
			setPosition(getX() + speed.first, getY() + speed.second);
			drainEnergy(walkingEnergy_);
		}
	}
	//cout << "POSICION PLAYER:" << getX() << "," << getY() << endl;
	//cout << "POSICION BARRA:" << energyLevel_->getX() << "," << energyLevel_->getY() << endl;
}

void Player::sleep()
{
}

void Player::getScared(int amount)
{
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
