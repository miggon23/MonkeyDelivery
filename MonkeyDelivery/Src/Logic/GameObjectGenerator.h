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
	int nBulls = 4, nCats = 13, nPlants = 14, nBats = 10, nScorpions = 8, nChest = 8, nRocks = 16;

	struct ChestDimension
	{
		int w = 50, h = 50;
	};
	struct Radios
	{
		int bullR = 60;
		int catR = 100;
		int plantsR = 80;
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
	static void generateLevel(Game* game)
	{
		gOGenerator.createChest();
		gOGenerator.creteBulls();
		gOGenerator.createScorpions();
		gOGenerator.createBats();
		gOGenerator.createPlants();
		gOGenerator.createCats();
		gOGenerator.createRocks();

		Point2D<int> mapOffset = { 1150, 800 }, newP; // variable para ajustar los objetos al mapa tras haber hecho una redimension de este
		Point2D<double> relative = { (double)(game->getWindowWidth() / 1800), (double)(game->getWindowHeight() / 1000) };
		for (int i = 0; i < gOGenerator.nChest; i++)
		{
			game->add(new InteractuableChest(game, (int)((gOGenerator.posChest[i].first + mapOffset.getX())*relative.getX()), 
				(int)((gOGenerator.posChest[i].second + mapOffset.getY()) * relative.getY()), gOGenerator.chestDimension_.w, gOGenerator.chestDimension_.h));

		}

		for (int i = 0; i < gOGenerator.nBulls; i++)
		{
			newP = gOGenerator.posBulls[i] + mapOffset;
			newP.setX((int)(newP.getX() * relative.getX()));
			newP.setY((int)(newP.getY() * relative.getY()));
			game->addEnemies(new Bull(game, gOGenerator.radios_.bullR, newP));
		}


		for (int i = 0; i < gOGenerator.nScorpions; i++)
		{
			newP = gOGenerator.posScorpions[i] + mapOffset;
			newP.setX((int)(newP.getX() * relative.getX()));
			newP.setY((int)(newP.getY() * relative.getY()));
			game->addEnemies(new Scorpion(game, gOGenerator.radios_.scorpionsR, newP));
		}


		for (int i = 0; i < gOGenerator.nBats; i++)
		{
			newP = gOGenerator.posBats[i] + mapOffset;
			newP.setX((int)(newP.getX() * relative.getX()));
			newP.setY((int)(newP.getY() * relative.getY()));
			game->addEnemies(new Bat(game, gOGenerator.radios_.batsR, newP, 3));


		}


		for (int i = 0; i < gOGenerator.nPlants; i++)
		{
			newP = gOGenerator.posPlants[i] + mapOffset;
			newP.setX((int)(newP.getX() * relative.getX()));
			newP.setY((int)(newP.getY() * relative.getY()));
			game->addEnemies(new Plant(game, gOGenerator.radios_.plantsR, newP));
		}


		for (int i = 0; i < gOGenerator.nCats; i++)
		{
			newP = gOGenerator.posCats[i] + mapOffset;
			newP.setX((int)(newP.getX() * relative.getX()));
			newP.setY((int)(newP.getY() * relative.getY()));
			game->addEnemies(new Cat(game, gOGenerator.radios_.catR, newP));
		}


		for (int i = 0; i < gOGenerator.nRocks; i++)
		{
			if(i%2==0) game->add(new Rock(game, (int)((gOGenerator.posRock[i].first + mapOffset.getX()) * relative.getX()), 
				(int)((gOGenerator.posRock[i].second + mapOffset.getY()) * relative.getY()), 1));
			else game->add(new Rock(game, (int)((gOGenerator.posRock[i].first + mapOffset.getX()) * relative.getX()), 
				(int)((gOGenerator.posRock[i].second + mapOffset.getY()) * relative.getY()), 2));
		}
	}
	static GameObjectGenerator gOGenerator;
};