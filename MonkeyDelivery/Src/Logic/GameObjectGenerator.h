#pragma once

#include "Game.h"
#include <vector>

class GameObjectGenerator
{
	int nBulls=4, nCats, nPlants, nBats, nScorpions, nChest=8;
	struct ChestDimension
	{
		int w=100, h=100;
	};

	ChestDimension chestDimension_;

	vector<pair<int, int>>posChest;

public:
	static void generateLevel(Game* game) //Lo llamas en las rocas
	{
		gOGenerator.createChest();

		for (int i = 0; i < gOGenerator.nChest; i++)
			game->add(new InteractuableChest(game, gOGenerator.posChest[i].first, gOGenerator.posChest[i].second, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));
		
		
	}

	static GameObjectGenerator gOGenerator;

	void createChest();
};