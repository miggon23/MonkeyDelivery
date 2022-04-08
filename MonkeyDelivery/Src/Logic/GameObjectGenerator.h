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

	ChestDimension chestDimension_;

	vector<pair<int, int>> posChest;
	vector<pair<int, int>> posBulls;
	vector<pair<int, int>> posCats;
	vector<pair<int, int>> posPlants;
	vector<pair<int, int>> posBats;
	vector<pair<int, int>> posScorpions;

public:
	static void generateLevel(Game* game) //Lo llamas en las rocas
	{
		gOGenerator.createChest();

		for (int i = 0; i < gOGenerator.nChest; i++)
			game->add(new InteractuableChest(game, gOGenerator.posChest[i].first, gOGenerator.posChest[i].second, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));
	}

	static GameObjectGenerator gOGenerator;

	void createChest();
	void creteBulls();
	void createCats();
	void createPlants();
	void createBats();
	void createScorpions();
};