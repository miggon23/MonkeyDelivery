#pragma once
#include "GameObject.h"
#include "SpawnZone.h"

class AnimationManager;
class Enemy : public GameObject
{
private:
	Uint32 lastUpdate_;//para timer del miedo
	
protected:


	bool collided = false;



	double speed;
	bool alive;
	double scariness_;
	float dieTime;
	SpawnZone zone;
	vector<Point2D<double>> checkpoints;
	int indexCheckPoint;
	bool back;

	AnimationManager* animationManager;	
	SDL_Rect textureRect;
	int timerAnimation;

	Uint32 timeOnFlash_;// timer morir enemigo
public:

	Enemy(Game* game, int Aleatorio, Point2D<int>centroRadio,AnimationManager* animation);
	~Enemy() {};

	void patrol(double speed);

	virtual void die();

	inline bool isAlive() { return alive; };
	inline void setAlive(bool l) { alive = l; };
	inline void addCheckPoint(Point2D<double> punto) { checkpoints.push_back(punto); };
	virtual void createCheckPoints() = 0; //Todos los enemigos crearan sus propios puntos de paso en su patrulla

	void spawn();
	void onCollision();
	virtual void checkDistance();
	inline virtual void setScariness(double fear) { scariness_ = fear; }
};