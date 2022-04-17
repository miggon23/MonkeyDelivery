#pragma once
#include "../Logic/GameObject.h"
#include "../Logic/SpawnZone.h"

class AnimationManager;
class Enemy : public GameObject
{
private:


protected:
	//timers
	Uint32 lastUpdate_;//para timer del miedo
	Uint32 respawnTimer;//timer respawn
	Uint32 timeOnFlash_;// timer morir enemigo
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
	bool startTimer = false;
	AnimationManager* animationManager;
	SDL_Rect textureRect;
	float timerAnimation;


	//movimiento enemigos respecto a camara
	Point2D<double> offsetCamera;

	int nearLimit_;

public:

	Enemy(Game* game, int radio, Point2D<int>centroRadio, AnimationManager* animation);
	~Enemy() {};

	void patrol(double speed);

	virtual void die();

	inline bool isAlive() { return alive; };
	inline void setAlive(bool l) { alive = l; };
	inline void addCheckPoint(Point2D<double> punto) { checkpoints.push_back(punto); };
	virtual void createCheckPoints() = 0; //Todos los enemigos crearan sus propios puntos de paso en su patrulla

	void spawn();
	void respawn();
	virtual void checkDistance();
	inline virtual void setScariness(double fear) { scariness_ = fear; }
	inline virtual void setResistance(int res) { resistence_ = res; }

	//ajuste del offset
	inline void changeOffset(Point2D<double> newMove) { offsetCamera = offsetCamera + newMove; }

	bool inPoint();
};