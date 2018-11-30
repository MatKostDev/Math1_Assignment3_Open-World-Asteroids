#pragma once
#include "GameObject.h"
#include "EnemyBullet.h"

class ShootingShip : public GameObject
{
public:
	ShootingShip(Vect2);

	float theta;
	float shootTimer;
	static std::vector<ShootingShip*> shootingShipList;

	EnemyBullet* shootBullet();
	void updatePhysics(float dt, Vect2 shipPosition);
};

