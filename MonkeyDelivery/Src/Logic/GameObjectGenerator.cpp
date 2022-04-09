#include "GameObjectGenerator.h"

GameObjectGenerator GameObjectGenerator::gOGenerator;

void GameObjectGenerator::createChest()
{
	posChest.push_back({ 400, 150 });		posChest.push_back({ 6350, 250 });
	posChest.push_back({ 4300, 1150 });		posChest.push_back({ 2060, 2500 });
	posChest.push_back({ 2320, 3320 });		posChest.push_back({ 6700, 4220 });
	posChest.push_back({ 6720, 5250 });		posChest.push_back({ 3530, 5900 });
}

void GameObjectGenerator::creteBulls()
{
	posBulls.push_back({ 6800, 1950 }); posBulls.push_back({ 6200, 5450 });
	posBulls.push_back({ 5300, 4700 }); posBulls.push_back({ 550, 4600 });
}

void GameObjectGenerator::createCats()
{
}

void GameObjectGenerator::createPlants()
{
}

void GameObjectGenerator::createBats()
{
}

void GameObjectGenerator::createScorpions()
{
}
