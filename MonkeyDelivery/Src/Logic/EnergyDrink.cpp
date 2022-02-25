#include "EnergyDrink.h"
#include "Game.h"
#include "Player.h"

EnergyDrink::EnergyDrink(Game* game) : InventoryObject(game)
{

}

EnergyDrink::~EnergyDrink()
{
}

bool EnergyDrink::useObject()
{
    return true;
}
