#pragma once
#include "../Logic/GameObject.h"
#include "../Logic/SpawnZone.h"

class AnimationManager;
class Enemy : public GameObject
{

protected:
	//TIMERS
	Uint32 lastUpdate_; //para timer del miedo
	Uint32 respawnTimer; //timer respawn
	Uint32 timeOnFlash_; // timer morir enemigo

	double speed_;
	double scariness_; //Miedo inflingido

	float dieTime;

	int maxFearPercent_; //porcentaje maximo de miedo que puede dar el enemigo
	int indexCheckPoint;
	int resistence_;
	int nearLimit_;
	int timeLimit_; //Lapso de tiempo que pasa desda la ultima vez que dio miedo, para que no sea constante
	

	bool collided = false;
	bool startTimer = false;
	bool back;
	bool alive;
	
	SpawnZone zone;
	vector<Point2D<double>> checkpoints;
	Point2D<double> offsetCamera; //movimiento enemigos respecto a camara
	

public:

	Enemy(Game* game, int radio, Point2D<int>centroRadio);
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
	inline void setScariness(double fear) { scariness_ = fear; }
	inline void setResistance(int res) { resistence_ = res; }
	inline void setMaxFearPercent(int max) { maxFearPercent_ = max; }

	//ajuste del offset
	inline void changeOffset(Point2D<double> newMove) { offsetCamera = offsetCamera + newMove; }

	bool inPoint();
};