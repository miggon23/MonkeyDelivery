#pragma once

#include "Game.h"
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
		int bullR = 100;
		int catR = 300;
		int plantsR = 400;
		int batsR = 100;
		int scorpionsR = 200;
	};

	ChestDimension chestDimension_;
	Radios radios_;

	vector<pair<int, int>> posChest;
	vector<Point2D<int>> posBulls;
	vector<pair<int, int>> posCats;
	vector<pair<int, int>> posPlants;
	vector<pair<int, int>> posBats;
	vector<pair<int, int>> posScorpions;

public:
	static void generateLevel(Game* game) //Lo llamas en las rocas
	{
		gOGenerator.createChest();
		gOGenerator.creteBulls();

		for (int i = 0; i < gOGenerator.nChest; i++)
			game->add(new InteractuableChest(game, gOGenerator.posChest[i].first, gOGenerator.posChest[i].second, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));

		for (int i = 0; i < gOGenerator.nBulls; i++)
			game->add(new Bull(game, gOGenerator.radios_.bullR, gOGenerator.posBulls[i], game->getAnimationManager()));
		
	}

	static GameObjectGenerator gOGenerator;

	void createChest();
	void creteBulls();
	void createCats();
	void createPlants();
	void createBats();
	void createScorpions();
};