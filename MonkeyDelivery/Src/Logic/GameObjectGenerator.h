#pragma once

#include "Game.h"


class GameObjectGenerator
{
	//int nBulls=4, nCats, nPlants, nBats, nScorpions, nChest=8;
	struct ChestDimension
	{
		int w=100, h=100;
	};

	ChestDimension chestDimension_;
public:
	static void generateLevel(Game* game) //Lo llamas en las rocas
	{
		game->add(new InteractuableChest(game, 350, 150, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));
		game->add(new InteractuableChest(game, 6350, 250, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));
		game->add(new InteractuableChest(game, 4300, 1150, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));
		game->add(new InteractuableChest(game, 2060, 2500, gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));
	}

	static GameObjectGenerator gOGenerator;
};

