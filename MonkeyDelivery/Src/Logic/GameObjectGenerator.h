#pragma once

#include "Game.h"
#include "../Enemies/Bull.h"
#include "../Enemies/Scorpion.h"
#include "../Enemies/Bat.h"
#include "../Enemies/Plant.h"
#include "../Enemies/Cat.h"
#include "../Items/Rock.h"
#include <vector>

class GameObjectGenerator
{
	int nBulls=4, nCats=13, nPlants=14, nBats=10, nScorpions=8, nChest=8, nRocks=16;

	struct ChestDimension
	{
		int w=50, h=50;
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
	vector<pair<int, int>> posRock;

	void createChest();
	void creteBulls();
	void createCats();
	void createPlants();
	void createBats();
	void createScorpions();
	void createRocks();

public:
	static void generateLevel(Game* game) //Lo llamas en las rocas
	{
		gOGenerator.createChest();
		//gOGenerator.createCarrots();
		gOGenerator.creteBulls();
		gOGenerator.createScorpions();
		gOGenerator.createBats();
		gOGenerator.createPlants();
		gOGenerator.createCats();
		gOGenerator.createRocks();

		Point2D<int> mapOffset = { 1150, 800 }; // variable para ajustar los objetos al mapa tras haber hecho una redimension de este

		for (int i = 0; i < gOGenerator.nChest; i++)
			game->add(new InteractuableChest(game, gOGenerator.posChest[i].first + mapOffset.getX(), gOGenerator.posChest[i].second + mapOffset.getY(), gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));

		for (int i = 0; i < gOGenerator.nBulls; i++)
			game->addEnemies(new Bull(game, gOGenerator.radios_.bullR, gOGenerator.posBulls[i] + mapOffset, game->getAnimationManager()));
		
		for (int i = 0; i < gOGenerator.nScorpions; i++)
			game->addEnemies(new Scorpion(game, gOGenerator.radios_.scorpionsR, gOGenerator.posScorpions[i] + mapOffset, game->getAnimationManager()));

		for (int i = 0; i < gOGenerator.nBats; i++)
			game->addEnemies(new Bat(game, gOGenerator.radios_.batsR, gOGenerator.posBats[i] + mapOffset, 3, game->getAnimationManager()));

		for (int i = 0; i < gOGenerator.nPlants; i++)
			game->addEnemies(new Plant(game, gOGenerator.radios_.plantsR, gOGenerator.posPlants[i] + mapOffset, game->getAnimationManager()));
		
		for (int i = 0; i < gOGenerator.nCats; i++)
			game->addEnemies(new Cat(game, gOGenerator.radios_.catR, gOGenerator.posCats[i] + mapOffset, game->getAnimationManager()));

		for (int i = 0; i < gOGenerator.nRocks; i++)
		{
			game->add(new Rock(game, gOGenerator.posRock[i].first + mapOffset.getX(), gOGenerator.posRock[i].second + mapOffset.getY(), sdlutils().rand().nextInt(1,2)));
		}
	}
	static GameObjectGenerator gOGenerator;
};