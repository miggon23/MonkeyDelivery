#pragma once
#include "GameObject.h"
#include "SpawnZone.h"

class AnimationManager;
class Enemy : public GameObject
{
private:


protected:

	Uint32 lastUpdate_;//para timer del miedo
	double speed;
	bool alive;
	double scariness_;
	float dieTime;
	SpawnZone zone;
	vector<Point2D<double>> checkpoints;
	int indexCheckPoint;
	bool back;
	int resistence_;
	bool collided = false;

	AnimationManager* animationManager;
	SDL_Rect textureRect;
	int timerAnimation;
	bool hasBeenKilled = false;
	Uint32 timeOnFlash_;// timer morir enemigo

	//movimiento enemigos respecto a camara
	Point2D<double> offsetCamera;

public:

	Enemy(Game* game, int Aleatorio, Point2D<int>centroRadio, AnimationManager* animation);
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
	inline virtual void setResistance(int res) { resistence_ = res; }

	//ajuste del offset
	inline void changeOffset(Point2D<double> newMove) { offsetCamera = offsetCamera + newMove; }
};