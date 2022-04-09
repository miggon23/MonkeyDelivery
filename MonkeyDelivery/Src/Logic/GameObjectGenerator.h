#pragma once

#include "Game.h"
#include "Bull.h"
#include "Scorpion.h"
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
		int bullR = 50;
		int catR = 100;
		int plantsR = 200;
		int batsR = 100;
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

public:
	static void generateLevel(Game* game) //Lo llamas en las rocas
	{
		gOGenerator.createChest();
		gOGenerator.creteBulls();
		gOGenerator.createScorpions();

		for (int i = 0; i < gOGenerator.nChest; i++)
			game->add(new InteractuableChest(game, gOGenerator.posChest[i].first, gOGenerator.posChest[i].second, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));

		for (int i = 0; i < gOGenerator.nBulls; i++)
			game->add(new Bull(game, gOGenerator.radios_.bullR, gOGenerator.posBulls[i], game->getAnimationManager()));
		
		for (int i = 0; i < gOGenerator.nScorpions; i++)
			game->add(new Scorpion(game, gOGenerator.radios_.scorpionsR, gOGenerator.posScorpions[i], game->getAnimationManager()));
	}

	static GameObjectGenerator gOGenerator;

	void createChest();
	void creteBulls();
	void createCats();
	void createPlants();
	void createBats();
	void createScorpions();
};