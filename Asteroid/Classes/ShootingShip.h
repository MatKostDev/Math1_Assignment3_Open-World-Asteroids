#pragma once
#include "GameObject.h"

class ShootingShip : public GameObject
{
public:
	ShootingShip(Vect2);

	float theta;

	void Shoot();
	void updatePhysics(float dt, Vect2 shipPosition);
};

