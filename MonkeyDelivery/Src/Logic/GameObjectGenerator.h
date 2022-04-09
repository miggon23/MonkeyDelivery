#pragma once

#include "Game.h"
#include "Bull.h"
#include "Scorpion.h"
#include "Bat.h"
#include "Plant.h"
#include "Cat.h"
#include <vector>

class GameObjectGenerator
{
	int nBulls=4, nCats=13, nPlants=14, nBats=10, nScorpions=8, nChest=8;

	struct ChestDimension
	{
		int w=100, h=100;
	};
	struct Radios 
	{
		int bullR = 60;
		int catR = 100;
		int plantsR = 150;
		int batsR = 50;
		int scorpionsR = 70;
	};

	ChestDimension chestDimension_;
	Radios radios_;

	vector<pair<int, int>> posChest;
	vector<Point2D<int>> posBulls;
	vector<Point2D<int>> posCats;
	vector<Point2D<int>> posPlants;
	vector<Point2D<int>> posBats;
	vector<Point2D<int>> posScorpions;

	void createChest();
	void creteBulls();
	void createCats();
	void createPlants();
	void createBats();
	void createScorpions();

public:
	static void generateLevel(Game* game) //Lo llamas en las rocas
	{
		gOGenerator.createChest();
		gOGenerator.creteBulls();
		gOGenerator.createScorpions();
		gOGenerator.createBats();
		gOGenerator.createPlants();
		gOGenerator.createCats();

		for (int i = 0; i < gOGenerator.nChest; i++)
			game->add(new InteractuableChest(game, gOGenerator.posChest[i].first, gOGenerator.posChest[i].second, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));

		for (int i = 0; i < gOGenerator.nBulls; i++)
			game->addEnemies(new Bull(game, gOGenerator.radios_.bullR, gOGenerator.posBulls[i], game->getAnimationManager()));
		
		for (int i = 0; i < gOGenerator.nScorpions; i++)
			game->addEnemies(new Scorpion(game, gOGenerator.radios_.scorpionsR, gOGenerator.posScorpions[i], game->getAnimationManager()));

		for (int i = 0; i < gOGenerator.nBats; i++)
			game->addEnemies(new Bat(game, gOGenerator.radios_.batsR, gOGenerator.posBats[i], 3, game->getAnimationManager()));

		for (int i = 0; i < gOGenerator.nPlants; i++)
			game->addEnemies(new Plant(game, gOGenerator.radios_.plantsR, gOGenerator.posPlants[i], game->getAnimationManager()));
		
		for (int i = 0; i < gOGenerator.nCats; i++)
			game->addEnemies(new Cat(game, gOGenerator.radios_.catR, gOGenerator.posCats[i], game->getAnimationManager()));
	}
	static GameObjectGenerator gOGenerator;
};